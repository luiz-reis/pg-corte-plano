#include "Mesh.h"

Mesh::Mesh(Material *mat)
{
	this->material = mat;
}

Mesh::~Mesh()
{
	//pensar se libera ou nao o material
}

Material* Mesh::get_material() const
{
	return this->material;
}

void Mesh::get_triangle(int i) const
{
	
}

void Mesh::add_vertex(Vetor vertex)
{
	
}

void Mesh::add_normal(Vetor normal)
{
	
}

void Mesh::add_triangle(int va, int vb, int vc, int na, int nb, int nc)
{
	
}