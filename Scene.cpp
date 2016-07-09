#include "Scene.h"
#include <algorithm>
#include <iostream>

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






