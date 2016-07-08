#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vetor.h"
#include "Material.h"

using namespace std;

class Mesh
{
private:
	struct Triangle
	{
		int va, vb, vc;
		int na, nb, nc;
	};
	
	Material *material;
	vector<Vetor> vertexs;
	vector<Vetor> normals;
	vector<Triangle> triangles;
	
public:
	Mesh(Material *mat);
	~Mesh();
	
	Material* get_material() const;
	void get_triangle(int i) const;
	
	void add_vertex(Vetor vertex);
	void add_normal(Vetor normal);
	void add_triangle(int va, int vb, int vc);	
};

#endif