#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Mesh.h"
#include "Light.h"
#include "Plane.h"
#include "Camera.h"

using namespace std;

class Scene
{
private:
	Camera *camera;
	vector<Mesh *> meshs;
	vector<Light *> lights;
public:
	Scene();
	Scene(Camera *camera);
	~Scene();
	
	Camera* get_camera() const;
	void set_camera(Camera *camera);
	
	void add_light(Light *light);
	void add_mesh(Mesh *mesh);
};

#endif