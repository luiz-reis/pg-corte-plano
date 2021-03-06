#include "Mesh.h"

Mesh::Mesh(Material *mat)
{
	this->material = mat;
}

Mesh::~Mesh()
{
	//pensar se libera ou nao o material
	delete this->material;
}

Mesh* Mesh::copy() const
{
	Material* mat = new Material(material->get_ka(), material->get_kd(), material->get_ks(), material->get_n(), material->get_od());
	Mesh* c = new Mesh(mat);
	for(auto &v : vertexs)
		c->add_vertex(v);
	
	return c;
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

int Mesh::add_vertex(Vetor vertex)
{
	vertexs.push_back(vertex);
	normals.push_back(Vetor());
	
	return vertexs.size() - 1;
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
	for(auto &n : normals)
		n = Vetor();
	
	for(auto t : triangles)
	{
		normals[t.va] = normals[t.va] + t.normal;
		normals[t.vb] = normals[t.vb] + t.normal;
		normals[t.vc] = normals[t.vc] + t.normal;
	}
	
	for(auto &n : normals)
		n.normalizar();
}




