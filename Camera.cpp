#include "Camera.h"
#include <cmath>

Camera::Camera(Vetor center, Vetor up, Vetor forward, float near, float far, float aspect)
{
	//center is a point 
	this->center = center;
	this->forward = forward;
	this->near = near;
	this->far = far;
	this->aspect = aspect;
	
	//build vectorial product between up and view
	this->z = up * this->forward;
	this->z.normalizar();
	this->forward.normalizar();
	this->up = this->z * this->forward;
	
	this->build_matrixs();
}

Camera::~Camera()
{
	
}

void Camera::build_matrixs()
{	
	/* VIEW MATRIX */
	Matrix4 t = {
		vec4(1,0,0,0), 
		vec4(0,1,0,0), 
		vec4(0,0,1,0), 
		vec4(-center.x,-center.y,-center.z,1)
	};
	
	Matrix4 m = {
		vec4(forward.x, up.x, z.x, 0), 
		vec4(forward.y, up.y, z.y, 0), 
		vec4(forward.z, up.z, z.z, 0), 
		vec4(0,0,0,1)
	};
	
/*	Matrix4 v = {
		vec4(forward.x, up.x, z.x, 0), 
		vec4(forward.y, up.y, z.y, 0), 
		vec4(forward.z, up.z, z.z, 0), 
		vec4(Vetor::p_escalar(forward, center), Vetor::p_escalar(up, center), Vetor::p_escalar(z, center), 1)
	}; */
	
	this->view = m * t;
	
	/* PROJECTION MATRIX */
	float left, right, top, bottom;
	float fov = 45;
	top = near * tan(M_PI/180 * fov/2);
	bottom = -top;
	right = top * aspect;
	left = -right;
	
	this->projection = {
		vec4(2*near/(right-left), 0, (right+left)/(right-left), 0),
		vec4(0, 2*near/(top-bottom), (top+bottom)/(top-bottom), 0),
		vec4(0, 0, -((far+near)/(far-near)), -(2*far*near/(far-near))),
		vec4(0, 0, -1, 0)
	}; 
}

Matrix4 Camera::get_projection() const
{
	return this->projection;
}