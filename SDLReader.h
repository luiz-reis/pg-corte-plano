#ifndef SDLREADER_H
#define SDLREADER_H

#include <string>
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "Util.h"

class SDLReader
{
private:
	static void read_object(string line, Mesh &mesh);
	static void read_camera(string line, Camera &camera);
	static void read_light(string line, Light &light);
	static void read_plane(string line, Plane &plane);
public:
	static void read_sdl(string filename, Scene &scene);
};

#endif