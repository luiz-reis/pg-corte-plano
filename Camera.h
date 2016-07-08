#ifndef CAMERA_H
#define CAMERA_H

#include "Vetor.h"
#include "Matrix4.h"

class Camera
{
private:
	float near, far, aspect;
	Vetor center, up, forward, z;
	Matrix4 projection, view;
	
	void build_matrixs();
public:
	Camera(Vetor center, Vetor up, Vetor forward, float near, float far, float aspect);
	~Camera();
	
	Matrix4 get_projection() const;
};

#endif