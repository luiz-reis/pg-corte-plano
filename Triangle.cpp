#include "Triangle.h"

Triangle::Triangle(int va, int vb, int vc, Vetor normal, Mesh *mesh)
{
	this->va = va;
	this->vb = vb;
	this->vc = vc;
	this->normal = normal;
	this->mesh = mesh;
}

void Triangle::pop_mesh()
{
	this->mesh->triangles.erase(this->mesh->triangles.begin() + i);
}

Mesh* Triangle::get_mesh() const
{
	return this->mesh;
}

Vetor Triangle::get_normal() const
{
	return this->normal;
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

int Triangle::get_iva() const
{
	return this->va;
}

int Triangle::get_ivb() const
{
	return this->vb;
}

int Triangle::get_ivc() const
{
	return this->vc;
}

Vetor Triangle::get_na() const
{
	return mesh->normals[va];
}

Vetor Triangle::get_nb() const
{
	return mesh->normals[vb];
}

Vetor Triangle::get_nc() const
{
	return mesh->normals[vc];
}