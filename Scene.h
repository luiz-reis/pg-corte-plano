#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Mesh.h"
#include "Light.h"
#include "Plane.h"
#include "Camera.h"
#include "Triangle.h"

using namespace std;

class Scene
{
private:
	Camera *camera;
	vector<Mesh *> meshs;
	vector<Light *> lights;
	float *buffer;
	void scan_triangle(Triangle triangle);
	
public:
	Scene();
	Scene(Camera *camera);
	~Scene();
	
	void set_buffer(int w, int h);
	float* get_buffer() const;
	
	Camera* get_camera() const;
	void set_camera(Camera *camera);
	
	void add_light(Light *light);
	void add_mesh(Mesh *mesh);
	
	void draw();
};

#endif