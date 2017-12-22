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
	static Mesh* read_object(string filename, Material *material)
	static Camera* read_camera(string filename)
	static Light* read_light(string filename, Material **material)
	static Plane* read_plane(string filename)
public:
	static void read_sdl(Scene &scene, string file_object, string file_camera, string file_light, string file_plane)
};

#endif
