#ifndef CAMERA_H
#define CAMERA_H

#include "Vetor.h"
#include "Matrix.h"

class Camera
{
private:
	float near, far;
	Vetor center, up, view;
	Matrix projection, ext;
public:
	Camera(Vetor center, Vetor up, Vetor view, float near, float far);
	~Camera();
};

#endif