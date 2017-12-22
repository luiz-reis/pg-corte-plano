#include "SDLReader.h"
#include "Util.h"
#include <vector>

Mesh* SDLReader::read_object(string filename, Material *material)
{
	Mesh *mesh = new Mesh(material);
	int v, t;
	
	Util::read_file(filename, [&v, &t, &mesh](string l, int i){
		if(l.size() == 0)
			return;

		vector<string> l_parm = Util::split_on_separators(l," ");
		if(i == 1) 
    {
			v = stoi(l_parm[0]);
      t = stoi(l_parm[1]);
		} 
    else if(i <= v + 1) 
    {
			float f1 = stof(l_parm[0]); 
			float f2 = stof(l_parm[1]); 
			float f3 = stof(l_parm[2]); 
			
			mesh->add_vertex(Vetor(f1, f2, f3));
		} 
    else if(i <= v + t + 1) 
    {
			int i1 = stoi(l_parm[0]) - 1; //por causa do indice do vertice no arquivo comecar a partir de 1
			int i2 = stoi(l_parm[1]) - 1;
			int i3 = stoi(l_parm[2]) - 1;
			mesh->add_triangle(i1, i2, i3); 
		}
	});

	mesh->build_vertex_normals();
	return mesh;
}

Camera* SDLReader::read_camera(string filename)
{
  Vector C, N, V;
  float d, hx, hy;
  Util::read_file(filename, [&C, &V, &N, &d, &hx, &hy](string line, int i) {
    vector<string> parm = Util::split_on_separators(line," ");
    float a = stof(parm[0]);
    float b = stof(parm[1]);
    float c = stof(parm[2]);
    
		switch(i)
    {
    	case 1:
      	C = Vector(a, b, c);
      	break;
      case 2:
      	N = Vector(a, b, c);
      	break;
      case 3:
      	V = Vector(a, b, c);
      	break;
      case 4:
      	d = a;
      	hx = b;
      	hy = c;
      	break;
    }
	});
	
	return new Camera(C, N, V, d, hx, hy);
}

Light* SDLReader::read_light(string filename, Material **material)
{
  Color Il;
  Vector Pl, Ia, Od;
  float ka, kd, ks, n;
  Util::read_file(filename, [&Pl, &Ia, &Od, &Il, &ka, &kd, &ks, &n](string line, int i) {
    vector<string> parm = Util::split_on_separators(line," ");
    
		switch(i)
    {
    	case 1:
      	Pl = Vector(stof(parm[0]), stof(parm[1]), stof(parm[2]));
      	break;
      case 2:
      	ka = stof(parm[0]);
      	break;
      case 3:
      	Ia = Vector(stof(parm[0]), stof(parm[1]), stof(parm[2]));
      	break;
      case 4:
      	kd = stof(parm[0]);
      	break;
      case 5:
      	Od = Vector(stof(parm[0]), stof(parm[1]), stof(parm[2]));
      	break;
      case 6:
      	ks = stof(parm[0]);
      	break;
      case 7:
      	Il = Color(stoi(parm[0]), stoi(parm[1]), stoi(parm[2]));
      	break;
      case 8:
      	n = stof(parm[0]);
      	break;
    }
  });
  
	*material = new Material(ka,kd,ks,n,Od);
  return new Light(Pl, 1, Il);
}

Plane* SDLReader::read_plane(string filename)
{
  Plane *plane;
	Util::read_file(filename, [&plane](string line, int i) {
    if(i > 1) 
      return;
    
    vector<string> parm = Util::split_on_separators(line," ");
    float a = stof(parm[0]);  
    float b = stof(parm[1]);  
    float c = stof(parm[2]); 
    float d = stof(parm[3]);
    float x0 = stof(parm[4]); 
    float y0 = stof(parm[5]);
    float z0 = stof(parm[6]);

    plane = new Plane(a, b, c, d, x0, y0, z0);
  });
  
  return plane;
}

void SDLReader::read_sdl(Scene &scene, string file_object, string file_camera, string file_light, string file_plane)
{
  Camera *camera = read_camera(file_camera);
  scene.set_camera(camera);
  Material *material;
  Light *light = read_light(file_light, &material);
  scene.add_light(light);
  Mesh *mesh = read_object(file_object, material);
  scene.add_mesh(mesh);
  Plane *plane = read_plane(file_plane);
  scene.set_plane(plane);
}
