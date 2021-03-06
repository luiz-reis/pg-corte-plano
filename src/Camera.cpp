#include "Camera.h"
#include <cmath>
#include <iostream>

Camera::Camera(Vetor C, Vetor N, Vetor V, float d, float hx, float hy)
{
	//center is a point 
	this->C = C;
	this->N = N;
	this->d = d;
	this->hx = hx;
	this->hy = hy;
	this->resx = 0;
	this->resy = 0;
	
	//build vectorial product between up and view
	this->up = N * V;
	this->up.normalizar();
	this->N.normalizar();
	this->V = this->N * this->up; // vericar ordem para saber se nverte ou nao
	
}

Camera::~Camera()
{
	
}

void Camera::set_screen_res(float resx, float resy)
{
	this->resx = resx;
	this->resy = resy;
}

Vetor Camera::world_to_view(Vetor point, bool vector)
{
	Vetor temp = vector ? point : point - this->C;
	float x = Vetor::p_escalar(this->up, temp);
	float y = Vetor::p_escalar(this->V, temp);
	float z = Vetor::p_escalar(this->N, temp);
	
	return Vetor(x, y, z); 
}

Vetor Camera::world_to_view(float x, float y, float z, bool vector)
{
	world_to_view(Vetor(x, y, z), vector);
}

Vetor Camera::world_to_screen(Vetor point)
{
	return view_to_screen(world_to_view(point));
}

Vetor Camera::world_to_screen(float x, float y, float z)
{
	world_to_screen(Vetor(x, y, z));
}

int Camera::get_resx() const
{
	return this->resx;
}

int Camera::get_resy() const
{
	return this->resy;
}

Vetor Camera::view_to_screen(Vetor point)
{
	float x = (point.x * this->d) / (point.z * this->hx);
	float y = (point.y * this->d) / (point.z * this->hy);
	
	x = (x + 1) * this->resx * 0.5f;
	y = (1 - y) * this->resy * 0.5f;
	
	int xint = round(x);//floor
	int yint = round(y);//floor
	
	return Vetor(xint, yint, 0);
}

Vetor Camera::view_to_screen(float x, float y, float z)
{
	view_to_screen(Vetor(x, y, z));
}
