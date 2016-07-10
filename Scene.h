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
	Plane *plane;
	float *buffer;
	float *zbuffer;
	Color ia;
	
	void scan_line(Triangle triangle);
	void fillBottomFlatTriangle(Vetor v1, Vetor v2, Vetor v3, Triangle triangle);
	void fillTopFlatTriangle(Vetor v1, Vetor v2, Vetor v3, Triangle triangle);
	
	Color ilumination(Vetor point, Vetor normal, Material material);
	void phong(Vetor point, Triangle triangle);
	
	float get_val_zbuffer(int x, int y) const;
	float get_val_zbuffer(Vetor point) const;
	
	void set_val_zbuffer(int x, int y, float val);
	void set_val_zbuffer(Vetor point, float val);
	
	bool bounds(float x, float y) const;
	
public:
	Scene();
	Scene(Camera *camera);
	~Scene();
	
	void set_buffer(int w, int h);
	float* get_buffer() const;
	
	void set_la(Color ia);
	
	void set_pixel_color(int x, int y, Color color);
	void set_pixel_color(Vetor p, Color color);
	
	Camera* get_camera() const;
	void set_camera(Camera *camera);
	
	void add_light(Light *light);
	void add_mesh(Mesh *mesh);
	
	void set_plane(Plane *plane);
	
	void draw();
};

#endif