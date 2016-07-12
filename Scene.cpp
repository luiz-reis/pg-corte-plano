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
	for(int i = 0; i < 3 * w * h; i+=3)
	{
		buffer[i + 0] = 1.0f;
		buffer[i + 1] = 0.0f;
		buffer[i + 2] = 0.0f;
	}
	
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
	if(!bounds(x, y))
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

void Scene::intersect_plane(Triangle t, Mesh& intersect)
{
	Vetor n = Vetor(plane->a, plane->b, plane->c);
	Vetor v0 = Vetor(plane->x0, plane->y0, plane->z0);
	
	Vetor va = t.get_va();
	Vetor vb = t.get_vb();
	Vetor vc = t.get_vc();
	
	Vetor p[3];
	int i[3];
	int count = 0;
	
	if(Vetor::p_escalar(n, va - v0) > 0) {
		i[count] = t.get_iva();
		p[count++] = va;
	}
	else
		p[2] = va;
	
	if(Vetor::p_escalar(n, vb - v0) > 0) {
		i[count] = t.get_ivb();
		p[count++] = vb;
	}
	else
		p[count + 1] = vb;
	
	if(Vetor::p_escalar(n, vc - v0) > 0) {
		i[count] = t.get_ivc();
		p[count++] = vc;
	}
	else
		p[count] = vc;
	
	if(count == 3) {
		std::cout << "3: " << t.i << std::endl;
		intersect.add_triangle(t.get_iva(), t.get_ivb(), t.get_ivc());
		return;
	}
	
	if(count == 1)
	{
		std::cout << "1: " << t.i << std::endl;
		Vetor l1 = Vetor::intersect_segment(n, v0, p[0], p[1]);
		Vetor l2 = Vetor::intersect_segment(n, v0, p[0], p[2]);
		
		int i1 = intersect.add_vertex(l1);
		int i2 = intersect.add_vertex(l2);
			
		intersect.add_triangle(i[0], i1, i2);
	}
	else if(count == 2)
	{
		std::cout << "2: " << t.i << std::endl;
		Vetor l1 = Vetor::intersect_segment(n, v0, p[0], p[2]);
		Vetor l2 = Vetor::intersect_segment(n, v0, p[1], p[2]);
		
		int i1 = intersect.add_vertex(l1);
		int i2 = intersect.add_vertex(l2);
			
		intersect.add_triangle(i[0], i1, i2);
		
		if(Vetor::colinear(p[0], l1, p[2]))
			intersect.add_triangle(i[0], i[1], i2);
		else
			intersect.add_triangle(i[0], i[1], i1);
	}
	else
	{
		std::cout << "0: " << t.i << std::endl;
	}
	
	
	/*Vetor li[2];
	int count = 0;
	
	Vetor temp = Vetor::intersect_segment(n, v0, va, vb);
	if(temp != Vetor::null) 
		li[count++] = temp;
		
	temp = Vetor::intersect_segment(n, v0, va, vc);
	if(temp != Vetor::null) 
		li[count++] = temp;
	
	temp = Vetor::intersect_segment(n, v0, vb, vc);
	if(temp != Vetor::null) 
		li[count++] = temp;
	
	if(count == 0) {
		//ou o triangulo ta todo dentro ou todo fora
		if(Vetor::p_escalar(n, va - v0) < 0)
			t.pop_mesh();
		
		return;
	}
	
	Vetor p[3];
	int i[3];
	count = 0;
	
	int sign = Vetor::p_escalar(n, va - v0);
	if(sign > 0) {
		i[count] = t.get_iva();
		p[count++] = va;
	}
	else
		p[2] = va;
	
	sign = Vetor::p_escalar(n, vb - v0);
	if(sign > 0) {
		i[count] = t.get_ivb();
		p[count++] = vb;
	}
	else
		p[1 + count] = vb;
	
	sign = Vetor::p_escalar(n, vc - v0);
	if(sign > 0) {
		i[count] = t.get_ivc();
		p[count++] = vc;
	}
	else
		p[count] = vc;
	
	
	t.pop_mesh();
	
	int i1 = t.get_mesh()->add_vertex(li[0]);
	int i2 = t.get_mesh()->add_vertex(li[1]);
	
	t.get_mesh()->add_triangle(i1, i2, i[0]);
	if(count > 1) {
		if(Vetor::colinear(p[0], li[0], p[2]))
			t.get_mesh()->add_triangle(i[0], i[1], i2);
		else
			t.get_mesh()->add_triangle(i[0], i[1], i1);
	}*/
}

void Scene::draw()
{
	vector<Mesh *> cut;
	if(plane != nullptr) 
	{
		//fazer intersecao plano com meshs
		for(auto &m : meshs)
		{
			Mesh *copy = m->copy();
			
			for(int i = 0; i < m->get_size_triangles(); ++i) {
				Triangle t = m->get_triangle(i);
				intersect_plane(t, *copy);
			}
		
			copy->build_vertex_normals();
			cut.push_back(copy);
		}
		
		for(auto &m : cut)
		{	
			for(int i = 0; i < m->get_size_triangles(); ++i) 
			{
				Triangle t = m->get_triangle(i);
				scan_line(t);
			}
		}
		
		for(auto &m : cut)
			delete m;
	}
	else
	{
		for(auto &m : meshs)
		{	
			for(int i = 0; i < m->get_size_triangles(); ++i) 
			{
				Triangle t = m->get_triangle(i);
				scan_line(t);
			}
		}
	}
}

void Scene::phong(Vetor point, Triangle triangle)
{
	if(!bounds(point.x, point.y))
		return;
		
	Vetor va = camera->world_to_view(triangle.get_va());
	Vetor vb = camera->world_to_view(triangle.get_vb());
	Vetor vc = camera->world_to_view(triangle.get_vc());
	
	Vetor abg = Vetor::get_abg(point, camera->view_to_screen(va), camera->view_to_screen(vb), camera->view_to_screen(vc));
	
	Vetor na = camera->world_to_view(triangle.get_na(), true);
	Vetor nb = camera->world_to_view(triangle.get_nb(), true);
	Vetor nc = camera->world_to_view(triangle.get_nc(), true);
	
	Vetor projected = Vetor::m_escalar(va, abg.x) + Vetor::m_escalar(vb, abg.y) + Vetor::m_escalar(vc, abg.z);
	Vetor normal = Vetor::m_escalar(na, abg.x) + Vetor::m_escalar(nb, abg.y) + Vetor::m_escalar(nc, abg.z);
	
	if(projected.z >= get_val_zbuffer(point))
		return;
	
	set_val_zbuffer(point, projected.z);
	
	Color color = ilumination(projected, normal, *triangle.get_mesh()->get_material());
	set_pixel_color(point, color);
}

Color Scene::ambient(float ka)
{
	return Color(ka * ia.r, ka * ia.g, ka * ia.b);
}

Color Scene::diffuse(float kd, Vetor L, Vetor n, Vetor od, Color light)
{
	float coef = kd * Vetor::p_escalar(n, L);
	return Color(coef * od.x * light.r, coef * od.y * light.g, coef * od.z * light.b);
}

Color Scene::specular(float ks, Vetor R, Vetor V, float n, Color light)
{
	float coef =  ks * pow(Vetor::p_escalar(R, V), n);
	return Color(coef * light.r, coef * light.g, coef * light.b);
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
	
	float nl = Vetor::p_escalar(normal, L);
	Vetor nl2 = Vetor::m_escalar(normal, 2.0f * nl);
	Vetor R = nl2 - L;
	R.normalizar();
	
	Color a = ambient(material.get_ka());
	Color d, s;
	if(Vetor::p_escalar(normal, L) >= 0)
	{
		d = diffuse(material.get_kd(), L, normal, material.get_od(), light.get_color());
		
		if(Vetor::p_escalar(R, V) >= 0)
			s = specular(material.get_ks(), R, V, material.get_n(), light.get_color());
	}
	
	Color color = a + d + s;
	
	return Color(min(color.r, 255), min(color.g, 255), min(color.b, 255));
}





