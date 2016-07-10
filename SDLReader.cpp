#include "SDLReader.h"
#include "Util.h"
#include <vector>

Mesh* SDLReader::read_object(string line)
{
	vector<string> parm = Util::split_on_separators(line," ");
	
	string filename = parm[0];
	float ka 	= stof(parm[1]);
	float kb 	= stof(parm[2]); 
	float kc 	= stof(parm[3]); 
	float n 	= stof(parm[4]);
	char r 		= stoi(parm[5]);
	char g 		= stoi(parm[6]);
	char b 		= stoi(parm[7]);
	
	Material *material = new Material(ka,kb,kc,n,Color(r,g,b));
	Mesh *mesh = new Mesh(material);
	int i = 0;
	int v;
	
	Util::read_file(filename, [&i,&v,&mesh](string l){
		if(l.size() == 0)
			return;

		vector<string> l_parm = Util::split_on_separators(l," ");
		if(i == 0) {
			v = stoi(l_parm[0]);
		} else if(i <= v) {
			float f1 = stof(l_parm[0]); 
			float f2 = stof(l_parm[1]); 
			float f3 = stof(l_parm[2]); 
			
			mesh->add_vertex(Vetor(f1, f2, f3));
		} else {

			int i1 = stoi(l_parm[0]) - 1; //por causa do indice do vertice no arquivo comecar a partir de 1
			int i2 = stoi(l_parm[1]) - 1;
			int i3 = stoi(l_parm[2]) - 1;
			mesh->add_triangle(i1, i2, i3); 
		}
		i++;
	});

	mesh->build_vertex_normals();
	return mesh;
}

Camera* SDLReader::read_camera(string line)
{
	vector<string> parm = Util::split_on_separators(line," ");
	float c1 	= stof(parm[0]);  
	float c2 	= stof(parm[1]);
	float c3 	= stof(parm[2]);
	float n1 	= stof(parm[3]);
	float n2 	= stof(parm[4]); 
	float n3 	= stof(parm[5]); 
	float v1 	= stof(parm[6]); 
	float v2 	= stof(parm[7]); 
	float v3 	= stof(parm[8]);
	float d 	= stof(parm[9]);
	float hx 	= stof(parm[10]);
	float hy 	= stof(parm[11]);
	
	return new Camera(Vetor(c1, c2, c3), Vetor(n1, n2, n3), Vetor(v1, v2, v3), d, hx, hy);
}

Light* SDLReader::read_light(string line)
{
	vector<string> parm = Util::split_on_separators(line," ");
	float p1 = stof(parm[0]);  
	float p2 = stof(parm[1]);  
	float p3 = stof(parm[2]); 
	float ip = stof(parm[3]); 
	
	char r 	= stoi(parm[4]);  
	char g 	= stoi(parm[5]);
	char b 	= stoi(parm[6]);
	
	return new Light(Vetor(p1,p2,p3), ip, Color(r,g,b));
}

Plane* SDLReader::read_plane(string line)
{
	vector<string> parm = Util::split_on_separators(line," ");
	float a = stof(parm[0]);  
	float b = stof(parm[1]);  
	float c = stof(parm[2]); 
	float d = stof(parm[3]); 
	
	return new Plane(a, b, c, d);
}

void SDLReader::read_sdl(string filename, Scene &scene)
{
	Util::read_file(filename, [&scene](string line){
		switch (line[0])
		{
			case 'm':
			{
				Mesh *mesh = read_object(line.substr(2));
				scene.add_mesh(mesh);
				break;
			}
			case 'c':
			{
				Camera *camera = read_camera(line.substr(2));
				scene.set_camera(camera);
				break;
			}
			case 'l':
			{
				Light *light = read_light(line.substr(2));
				scene.add_light(light);
				break;
			}
			case 'p':
			{
				Plane *plane = read_plane(line.substr(2));
				scene.set_plane(plane);
				break;
			}
			case 'a':
			{
				
				break;
			}
		}
	});
}

