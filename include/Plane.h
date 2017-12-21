#ifndef PLANE_H
#define PLANE_H

class Plane
{
public:
	float a, b, c, d, x0, y0, z0;
	Plane(float a, float b, float c, float d, float x0, float y0, float z0);
	~Plane();
};

#endif