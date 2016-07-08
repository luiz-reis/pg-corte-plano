#include "Scene.h"

Scene::Scene() 
	: Scene(nullptr)
{
	
}

Scene::Scene(Camera *camera)
{
	this->camera = camera;
}

Scene::~Scene()
{
	
}

Camera* Scene::get_camera() const
{
	return this->camera;
}

void Scene::set_camera(Camera *camera)
{
	
}

void Scene::add_light(Light *light)
{

}

void Scene::add_mesh(Mesh *mesh)
{
	
}