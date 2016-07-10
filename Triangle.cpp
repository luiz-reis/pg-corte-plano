#include "Triangle.h"

Triangle::Triangle(int va, int vb, int vc, Vetor normal, Mesh *mesh)
{
	this->va = va;
	this->vb = vb;
	this->vc = vc;
	this->normal = normal;
	this->mesh = mesh;
}

Vetor Triangle::get_abg(Vetor point) const
{	
	Vetor v0 = this->mesh->vertexs[va];
	
	Vetor u = this->mesh->vertexs[vb] - v0;
	Vetor v = this->mesh->vertexs[vc] - v0;
	Vetor w = point - v0;
	
	float uv = Vetor::p_escalar(u, v);
	float uu = Vetor::p_escalar(u, u);
	float vv = Vetor::p_escalar(v, v);
	
	float d = uv * uv - uu * vv;
	float beta = uv * Vetor::p_escalar(w, v) - vv * Vetor::p_escalar(w, u);
	float gama = uv * Vetor::p_escalar(w, u) - uu * Vetor::p_escalar(w, v);
	beta /= d;
	gama /= d;
	float alpha = 1 - beta - gama;
	
	return Vetor(alpha, beta, gama);
}

Mesh* Triangle::get_mesh() const
{
	return this->mesh;
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