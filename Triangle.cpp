#include "Triangle.h"

Triangle::Triangle(int va, int vb, int vc, Vetor normal, Mesh *mesh)
{
	this->va = va;
	this->vb = vb;
	this->vc = vc;
	this->normal = normal;
	this->mesh = mesh;
}

Vetor Triangle::get_va() const
{
	return mesh->vertexs[va];
}

Vetor Triangle::get_vb() const
{
	return mesh->vertexs[vb];
}

Vetor Triangle::get_vc() const
{
	return mesh->vertexs[vc];
}