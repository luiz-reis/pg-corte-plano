#ifndef CAMERA_H
#define CAMERA_H

#include "Vetor.h"
#include "Matrix4.h"

class Camera
{
private:
	float d, hx, hy;
	float resx, resy;
	Vetor C, N, V, up;
public:
	Camera(Vetor C, Vetor N, Vetor V, float d, float hx, float hy);
	~Camera();
	
	int get_resx() const;
	int get_resy() const;
	
	void set_screen_res(float resx, float resy);
	
	Vetor world_to_view(Vetor point, bool vector = false);
	Vetor world_to_view(float x, float y, float z, bool vector = false);
	
	Vetor view_to_screen(Vetor point);
	Vetor view_to_screen(float x, float y, float z);
		
	Vetor world_to_screen(Vetor point);
	Vetor world_to_screen(float x, float y, float z);
};

#endif