#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vetor.h"
#include "Material.h"
#include "Triangle.h"

using namespace std;

class Triangle;
class Mesh
{
private:	
	Material *material;
	vector<Vetor> vertexs;
	vector<Vetor> normals;
	vector<Triangle> triangles;
	
public:
	friend class Triangle;
	
	Mesh(Material *mat);
	~Mesh();
	
	Mesh* copy() const;
	
	void build_vertex_normals();
	
	Material* get_material() const;
	Triangle get_triangle(int i) const;
	int get_size_triangles() const;
	
	int add_vertex(Vetor vertex);
	void add_normal(Vetor normal);
	void add_triangle(int va, int vb, int vc);	
};

#endif