#include "Scene.h"
#include "Util.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cfloat>

Scene::Scene() 
	: Scene(nullptr)
{
	
}

Scene::Scene(Camera *camera)
{
	this->camera = camera;
	this->buffer = nullptr;
	this->zbuffer = nullptr;
	this->plane = nullptr;
}

Scene::~Scene()
{
	if(camera != nullptr)
		delete camera;
	
	for(auto m : meshs)
		delete m;
	
	for(auto l : lights)
		delete l;
	
	if(plane != nullptr)
		delete plane;
	
	if(buffer != nullptr)
		delete[] buffer;
	
	if(zbuffer != nullptr)
		delete[] zbuffer;
	
	meshs.clear();
	lights.clear();
}

Camera* Scene::get_camera() const
{
	return this->camera;
}

void Scene::set_camera(Camera *camera)
{
	this->camera = camera;
}

void Scene::set_la(Color ia)
{
	this->ia = ia;
}

void Scene::set_buffer(int w, int h)
{
	if(buffer != nullptr)
		delete[] buffer;
	
	if(zbuffer != nullptr)
		delete[] zbuffer;
	
	buffer = new float[3 * w * h];
	for(int i = 0; i < 3 * w * h; ++i)
		buffer[i] = 0.0f;
	
	zbuffer = new float[w * h];
	for(int i = 0; i < w * h; ++i)
		zbuffer[i] = FLT_MAX;
}

bool Scene::bounds(float x, float y) const
{
	return !(x < 0 || x >= camera->get_resx() || y < 0 || y >= camera->get_resy());
}

float* Scene::get_buffer() const
{
	return this->buffer;
}

void Scene::add_light(Light *light)
{
	lights.push_back(light);
}

void Scene::add_mesh(Mesh *mesh)
{
	meshs.push_back(mesh);
}

void Scene::set_plane(Plane *plane)
{
	this->plane = plane;
}

void Scene::set_pixel_color(Vetor p, Color color)
{
	set_pixel_color(p.x, p.y, color);
}

void Scene::set_pixel_color(int x, int y, Color color)
{
	if(!bounds(x, y))
		return;
	
	buffer[y * camera->get_resx() * 3 + x * 3 + 0] = color.r/255.0f;
	buffer[y * camera->get_resx() * 3 + x * 3 + 1] = color.g/255.0f;
	buffer[y * camera->get_resx() * 3 + x * 3 + 2] = color.b/255.0f;
}

float Scene::get_val_zbuffer(int x, int y) const
{
	if(!bounds(x, y))
		return 0;
	
	return zbuffer[y * camera->get_resx() + x];
}

float Scene::get_val_zbuffer(Vetor point) const
{
	return get_val_zbuffer(point.x, point.y);
}
	
void Scene::set_val_zbuffer(int x, int y, float val)
{
	if(x < 0 || x > camera->get_resx() || y < 0 || y > camera->get_resy())
		return;
	
	zbuffer[y * camera->get_resx() + x] = val;
}

void Scene::set_val_zbuffer(Vetor point, float val)
{
	set_val_zbuffer(point.x, point.y, val);
}

void Scene::fillBottomFlatTriangle(Vetor v1, Vetor v2, Vetor v3, Triangle triangle)
{
	float xmin, xmax;
	float invsamin, invsamax;

	xmin = xmax = v1.x;

	invsamin = (float)(v2.x - v1.x) / (v2.y - v1.y);
	invsamax = (float)(v3.x - v1.x) / (v3.y - v1.y);
	
	for(int scany = v1.y; scany <= v2.y; ++scany)
	{
		int ini = xmin, fim = xmax;
		if(fim < ini) swap(ini, fim);
		
		for(int i = ini; i <= fim; ++i)
		{
			Vetor point = Vetor(i, scany, 0);
			phong(point, triangle);
		}
	
		xmin += invsamin;
		xmax += invsamax;
	}
}

void Scene::fillTopFlatTriangle(Vetor v1, Vetor v2, Vetor v3, Triangle triangle)
{
	float xmin, xmax;
	float invsamin, invsamax;

	xmin = xmax = v3.x;

	invsamin = (float)(v3.x - v1.x) / (v3.y - v1.y);
	invsamax = (float)(v3.x - v2.x) / (v3.y - v2.y);
	
	for(int scany = v3.y; scany > v1.y; --scany)
	{
		int ini = xmin, fim = xmax;
		if(fim < ini) swap(ini, fim);
		
		for(int i = ini; i <= fim; ++i)
		{
			Vetor point = Vetor(i, scany, 0);
			phong(point, triangle);
		}
	
		xmin -= invsamin;
		xmax -= invsamax;
	}
}

void Scene::scan_line(Triangle triangle)
{
	Vetor pva = camera->world_to_screen(triangle.get_va());
	Vetor pvb = camera->world_to_screen(triangle.get_vb());
	Vetor pvc = camera->world_to_screen(triangle.get_vc());
	
	Vetor v[] = { pva, pvb, pvc };
	
	//ordeno vertices em y
	if(v[0].y > v[1].y)
		swap(v[0], v[1]);
	
	if(v[1].y > v[2].y) {
		swap(v[1], v[2]);
		
		if(v[0].y > v[1].y)
			swap(v[0], v[1]);
	}
	
	if(v[1].y == v[2].y)
		fillBottomFlatTriangle(v[0], v[1], v[2], triangle);
	else if(v[0].y == v[1].y)
		fillTopFlatTriangle(v[0], v[1], v[2], triangle);
	else
	{
		int x = (int)(v[0].x + ((float)(v[1].y - v[0].y) / (float)(v[2].y - v[0].y)) * (v[2].x - v[0].x));
		Vetor v4 = Vetor(x, v[1].y, 0);
		
		fillBottomFlatTriangle(v[0], v[1], v4, triangle);
		fillTopFlatTriangle(v[1], v4, v[2], triangle);
	}
}

void Scene::intersect_plane(Triangle t)
{
	Vetor n = Vetor(plane->a, plane->b, plane->c);
	Vetor v0 = Vetor(plane->xa, plane->y0, plane->z0);
	
	Vetor va = t.get_va();
	Vetor vb = t.get_va();
	Vetor vc = t.get_va();
	
	Vetor p0, p1;
	Vetor l0, l1;
	
	
}

void Scene::draw()
{
	//fazer intersecao plano com meshs
	for(auto &m : meshs)
	{
		for(int i = 0; i < m->get_size_triangles(); ++i) {
			Triangle t = m->get_triangle(i);
			intersect_plane(t);
		}
	}
	
	for(auto &m : meshs)
	{
		for(int i = 0; i < m->get_size_triangles(); ++i) {
			Triangle t = m->get_triangle(i);
			scan_line(t);
		}
	}
}

void Scene::phong(Vetor point, Triangle triangle)
{
	if(!bounds(point.x, point.y))
		return;
	
	Vetor abg = triangle.get_abg(point);
	Vetor projected = Vetor::m_escalar(triangle.get_va(), abg.x) + Vetor::m_escalar(triangle.get_vb(), abg.y) + Vetor::m_escalar(triangle.get_vc(), abg.z);
	Vetor normal = Vetor::m_escalar(triangle.get_na(), abg.x) + Vetor::m_escalar(triangle.get_nb(), abg.y) + Vetor::m_escalar(triangle.get_nc(), abg.z);
	
	if(projected.z >= get_val_zbuffer(point))
		return;
	
	set_val_zbuffer(point, projected.z);
	
	Color color = ilumination(projected, normal, *triangle.get_mesh()->get_material());
	set_pixel_color(point, color);
}

Color Scene::ilumination(Vetor point, Vetor normal, Material material)
{
	Light light = *lights[0];

	Vetor V = -point;
	Vetor L = camera->world_to_view(light.get_pos()) - point;
	
	V.normalizar();
	L.normalizar();
	normal.normalizar();
	
	if(Vetor::p_escalar(normal, V) < 0)
		normal = -normal;

	int r = Util::clamp(material.get_ka() * ia.r, 0, 255);
	int g = Util::clamp(material.get_ka() * ia.g, 0, 255);
	int b = Util::clamp(material.get_ka() * ia.b, 0, 255);

	float nl = Vetor::p_escalar(normal, L);
	
	if(nl >= 0) {
		float difusa = material.get_kd() * nl;
		int r_difusa = Util::clamp(material.get_od().r * light.get_color().r * difusa, 0, 255);
		int g_difusa = Util::clamp(material.get_od().g * light.get_color().g * difusa, 0, 255);
		int b_difusa = Util::clamp(material.get_od().b * light.get_color().b * difusa, 0, 255);
		
		r += Util::clamp(r_difusa, 0, 255);
		g += Util::clamp(g_difusa, 0, 255);
		b += Util::clamp(b_difusa, 0, 255);

		Vetor nl2 = Vetor::m_escalar(normal, 2.0f * nl);
		Vetor R = normal - L;
		R.m_escalar(2.0f * nl);
		R.normalizar();
		
		float rv = Vetor::p_escalar(V, R);
		if(rv >= 0) {
			float rvn = pow(rv, material.get_n());
			float especular = material.get_ks() * rvn;
			r += Util::clamp(especular * light.get_color().r, 0, 255);
			g += Util::clamp(especular * light.get_color().g, 0, 255);
			b += Util::clamp(especular * light.get_color().b, 0, 255);
		}
	}
	
	return Color(r, g, b);
}





