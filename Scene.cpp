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

void Scene::scan_triangle(Triangle triangle)
{	
	Vetor va = triangle.get_va();
	Vetor vb = triangle.get_vb();
	Vetor vc = triangle.get_vc();
	
	std::cout << va << vb << vc << std::endl;
	
	Vetor vva = camera->world_to_view(va);
	Vetor vvb = camera->world_to_view(vb);
	Vetor vvc = camera->world_to_view(vc);
	
	Vetor pva = camera->view_to_screen(vva);
	Vetor pvb = camera->view_to_screen(vvb);
	Vetor pvc = camera->view_to_screen(vvc);
	
	Vetor vertices[] = { pva, pvb, pvc };
	
	//ordeno vertices em y
	if(vertices[0].y > vertices[1].y)
		swap(vertices[0], vertices[1]);
	
	if(vertices[1].y > vertices[2].y) {
		swap(vertices[1], vertices[2]);
		
		if(vertices[0].y > vertices[1].y)
			swap(vertices[0], vertices[1]);
	}
	
	std::cout << vertices[0] << vertices[1] << vertices[2] << std::endl;
	
	float xmin, xmax, y;
	float amin, amax;
	
	xmin = xmax = vertices[0].x;
	y = vertices[0].y;
	
	amin = (vertices[2].y - y) / (vertices[2].x - xmin);
	amax = (vertices[1].y - y) / (vertices[1].x - xmin);
	
	if(vertices[2].x > vertices[1].x)
		swap(amin, amax);

	while(y <= vertices[2].y)
	{
		if(y >= vertices[1].y){
			float temp = (vertices[2].y - vertices[1].y) / (vertices[2].x - vertices[1].x);
			if(vertices[2].x > vertices[1].x)
				amin = temp;
			else 
				amax = temp;
		}
		
		for(int i = xmin; i <= xmax; ++i)
		{
			Vetor point = Vetor(i, y, 0);
			std::cout << point << std::endl;
		}
		
		y += 1;
		xmin = xmin + 1 / amin;
		xmax = xmax + 1 / amax;
	}	
}

void Scene::draw()
{
	for(auto &m : meshs)
	{
		for(int i = 0; i < m->get_size_triangles(); ++i) {
			Triangle t = m->get_triangle(i);
			scan_triangle(t);
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





