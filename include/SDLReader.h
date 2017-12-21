#ifndef SDLREADER_H
#define SDLREADER_H

#include <string>
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"

class SDLReader
{
private:
	static Mesh* read_object(string line);
	static Camera* read_camera(string line);
	static Light* read_light(string line);
	static Plane* read_plane(string line);
public:
	static void read_sdl(string filename, Scene &scene);
};

#endif