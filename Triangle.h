#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vetor.h"
#include "Mesh.h"

class Mesh;
class Triangle
{
private:
	int va, vb, vc;
	float alpha, beta, gama;
	Vetor normal;
	Mesh* mesh;
public:
	friend class Mesh;
	Triangle(int va, int vb, int vc, Vetor normal, Mesh *mesh);
	Vetor get_va() const;
	Vetor get_vb() const;
	Vetor get_vc() const;	
};

#endif