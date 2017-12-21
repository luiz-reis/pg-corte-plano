#include "Plane.h"

Plane::	Plane(float a, float b, float c, float d, float x0, float y0, float z0)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->x0 = x0;
	this->y0 = y0;
	this->z0 = z0;
}

Plane::~Plane()
{
	
}