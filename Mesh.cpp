#include "Mesh.h"

Mesh::Mesh(Material *mat)
{
	this->material = mat;
}

Mesh::~Mesh()
{
	//pensar se libera ou nao o material
}

Vetor Mesh::get_abg(int triangle, Vetor point)
{
	Triangle t = triangles[triangle];
	
	Vetor v0 = vertexs[t.va];
	
	Vetor u = vertexs[t.vb] - v0;
	Vetor v = vertexs[t.vc] - v0;
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

Material* Mesh::get_material() const
{
	return this->material;
}

Triangle Mesh::get_triangle(int i) const
{
	return triangles[i];
}

int Mesh::get_size_triangles() const
{
	return triangles.size();
}

void Mesh::add_vertex(Vetor vertex)
{
	vertexs.push_back(vertex);
	normals.push_back(Vetor());
}

void Mesh::add_triangle(int va, int vb, int vc)
{
	Vetor v = vertexs[va];
	
	Vetor v1 = vertexs[vb] - v;
	Vetor v2 = vertexs[vc] - v;
	
	Vetor normal = v1 * v2;
	normal.normalizar();
	
	triangles.push_back(Triangle(va, vb, vc, normal, this));
}

void Mesh::build_vertex_normals()
{
	for(auto t : triangles)
	{
		normals[t.va] = normals[t.va] + t.normal;
		normals[t.vb] = normals[t.vb] + t.normal;
		normals[t.vc] = normals[t.vc] + t.normal;
	}
	
	for(auto &n : normals)
		n.normalizar();
}








