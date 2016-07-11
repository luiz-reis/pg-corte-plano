#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vetor.h"
#include "Mesh.h"

class Mesh;
class Triangle
{
private:
	int va, vb, vc, i;
	float alpha, beta, gama;
	Vetor normal;
	Mesh* mesh;
public:
	friend class Mesh;
	Triangle(int va, int vb, int vc, Vetor normal, Mesh *mesh);
	
	Vetor get_abg(Vetor point) const;
	
	Mesh* get_mesh() const;
	
	Vetor get_va() const;
	Vetor get_vb() const;
	Vetor get_vc() const;
	
	int get_iva() const;
	int get_ivb() const;
	int get_ivc() const;	
	
	Vetor get_na() const;
	Vetor get_nb() const;
	Vetor get_nc() const;
	
	Vetor get_normal() const;
	
	void pop_mesh();
};

#endif