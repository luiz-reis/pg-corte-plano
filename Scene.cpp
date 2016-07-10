#include "Scene.h"
#include <algorithm>
#include <iostream>
#include <cmath>

Scene::Scene() 
	: Scene(nullptr)
{
	
}

Scene::Scene(Camera *camera)
{
	this->camera = camera;
	this->buffer = nullptr;
}

Scene::~Scene()
{
	if(camera != nullptr)
		delete camera;
	
	for(auto m : meshs)
		delete m;
	
	for(auto l : lights)
		delete l;
	
	if(buffer != nullptr)
		delete[] buffer;
	
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

void Scene::set_buffer(int w, int h)
{
	if(buffer != nullptr)
		delete[] buffer;
	
	buffer = new float[3 * w * h];
	for(int i = 0; i < 3 * w * h; ++i)
		buffer[i] = 0.0f;
}

float * Scene::get_buffer() const
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

void Scene::set_pixel_color(Vetor p, Color color)
{
	set_pixel_color(p.x, p.y, color);
}

void Scene::set_pixel_color(int x, int y, Color color)
{
	if(x < 0 || x > camera->get_resx() || y < 0 || y > camera->get_resy())
		return;
	
	buffer[y * camera->get_resx() * 3 + x * 3 + 0] = color.r/255.0f;
	buffer[y * camera->get_resx() * 3 + x * 3 + 1] = color.g/255.0f;
	buffer[y * camera->get_resx() * 3 + x * 3 + 2] = color.b/255.0f;
}

void fillBottomFlatTriangle(Vetor v1, Vetor v2, Vetor v3)
{
	float xmin, xmax;
	float invsamin, invsamax;

	xmin = xmax = v1.x;

	invsamin = (v2.x - v1.x) / (v2.y - v1.y);
	invsamax = (v3.x - v1.x) / (v3.y - v1.y);
	
	for(int scany = v1.y; scany <= v2.y; ++scany)
	{
		for(int i = xmin; i <= xmax; ++i)
		{
			Vetor point = Vetor(i, scany, 0);
			
			set_pixel_color(point, Color(255,0,0));
		}
	
		xmin += invsamin;
		xmax += invsamax;
	}
}

void Scene::scan_line(Triangle triangle)
{	
	Vetor va = triangle.get_va();
	Vetor vb = triangle.get_vb();
	Vetor vc = triangle.get_vc();
	
	Vetor vva = camera->world_to_view(va);
	Vetor vvb = camera->world_to_view(vb);
	Vetor vvc = camera->world_to_view(vc);
	
	Vetor pva = camera->view_to_screen(vva);
	Vetor pvb = camera->view_to_screen(vvb);
	Vetor pvc = camera->view_to_screen(vvc);
	
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
		fillBottomFlatTriangle(v[0], v[1], v[2]);
	else if(v[0].y == v[1].y)
		fillTopFlatTriangle(v[0], v[1], vp[2]);
	else
	{
		Vetor v4 = Vetor((int)(v[0].x + ((float)(v[1].y - v[0].y) / (float)(v[2].y - v[0].y)) * (v[2].x - v[0].x)), v[1].y);
		
		fillBottomFlatTriangle(v[0], v[1], v4);
		fillTopFlatTriangle(v[1], v4, v[2]);
	}
}

void Scene::draw()
{
	for(auto &m : meshs)
	{
		for(int i = 0; i < m->get_size_triangles(); ++i) {
			Triangle t = m->get_triangle(i);
			scan_line(t);
		}
	}
}

Color Scene::lumination(Vetor point, Vetor normal, Material material)
{
	if(Vetor::p_escalar(normal, point) < 0){
		normal = Vetor::m_escalar(normal, -1);
	}

	int r = Util::clamp(material.get_ka()*ia.r, 0, 255);
	int g = Util::clamp(material.get_ka()*ia.g, 0, 255);
	int b = Util::clamp(material.get_ka()*ia.b, 0, 255);
	Color parte1 = new Color(r_parte1, g_parte1, b_parte1);

	Vetor L = lights[0].pos - point;
	float nl = Vetor::p_escalar(normal, L)
	
	if(Vetor::p_escalar(normal, L) >= 0){
		float parte2 = material.get_kd() * nl;
		int r_parte2 = Util::clamp(material.get_od().r*lights[0].color.r, 0, 255);
		int g_parte2 = Util::clamp(material.get_od().g*lights[0].color.g, 0, 255);
		int b_parte2 = Util::clamp(material.get_od().b*lights[0].color.b, 0, 255);
		int r += Util::clamp(r_parte2, 0, 255);
		int g += Util::clamp(g_parte2, 0, 255);
		int b += Util::clamp(b_parte2, 0, 255);

		Vetor 2n = Vetor::m_escalar(normal, 2.0f);
		Vetor R = Vetor::m_escalar(2n, nl) - L;
		if(Vetor::p_escalar(point, R) >= 0){
			float rv = pow(Vetor::p_escalar(R, point), material.get_n());
			float parte3 = material.get_ks()*rv;
			int r += Util::clamp(parte3*lights[0].color.r, 0, 255);
			int g += Util::clamp(parte3*lights[0].color.g, 0, 255);
			int b += Util::clamp(parte3*lights[0].color.b, 0, 255);
		}
		
	}

	return Color(r, g, b);
}





