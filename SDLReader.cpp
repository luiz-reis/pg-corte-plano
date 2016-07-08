#include "SDLReader.h"
#include "vector<>"

void SDLReader::read_object(string line, Mesh &mesh)
{
	vector<string> parm = Util::split_on_separators(line," ");
	string filename = parm[0];
	int i = 0;
	int v;
	Util::read_file(filename, [&i,&v,&mesh](string l){
		vector<string> l_parm = Util::split_on_separators(l," ");
		int v;
		if(i == 0)
		{
			v = stoi(l_parm[0]);
		}else if(i < v){
			float f1 = stof(l_parm[0]); 
			float f2 = stof(l_parm[1]); 
			float f3 = stof(l_parm[0]); 
			mesh.add_vertex(Vetor(f1,f2,f3));
		}else{
			int i1 = stoi(l_parm[0]); 
			int i2 = stoi(l_parm[1]);
			int i3 = stoi(l_parm[2]);
			mesh.add_triangle(i1,i2,i3); 
		}
		i++;
	});
	float ka = stof(parm[1]);
	float kb = stof(parm[2]); 
	float kc = stof(parm[3]); 
	float n = stof(parm[4]);
	char r = stoi(parm[5]);
	char g = stoi(parm[6]);
	char b = stoi(parm[7]);
	Material *material = new Material(ka,kb,kc,n,Color(r,g,b));
	//Mesh.set_material(material);
}

void SDLReader::read_camera(string line, Camera &camera)
{
	vector<string> parm = Util::split_on_separators(line," ");
	float c1 = stof(parm[0]);  
	float c2 = stof(parm[1]);
	float c3 = stof(parm[2]);
	float u1 = stof(parm[3]);
	float u2 = stof(parm[4]); 
	float u3 = stof(parm[5]); 
	float f1 = stof(parm[6]); 
	float f2 = stof(parm[7]); 
	float f3 = stof(parm[8]);
	float n = stof(parm[9]);
	float f = stof(parm[10]);
	float hx = stof(parm[11]);
	float hy = stof(parm[12]);
	Camera *camera = new Camera(Vetor(c1,c2,c3),Vetor(u1,u2,u3),Vetor(f1,f2,f3),n,f,(hx/hy));
}

void SDLReader::read_light(string line, Light &light)
{
	vector<string> parm = Util::split_on_separators(line," ");
	float p1 = stof(parm[0]);  
	float p2 = stof(parm[1]);  
	float p3 = stof(parm[2]); 
	float ip = stof(parm[3]); 
	char r = stoi(parm[4]);  
	char g = stoi(parm[5]);
	char b = stoi(parm[6]);
	Light *light = new Light(Vetor(p1,p2,p3),ip,Color(r,g,b));
}

void SDLReader::read_plane(string line, Plane &plane)
{

}

void SDLReader::read_sdl(string filename, Scene &scene)
{
	Util::read_file(filename,[](string line){
		switch (line[0])
		{
			case 'm':
				Mesh *mesh = new Mesh();
				read_object(line.substr(2), *mesh);
				break;
			case 'c':
				Camera *camera = new Camera();
				read_camera(line.substr(2), *camera);
				break;
			case 'l':
				Light *light = new Light();
				read_light(line.substr(2), *light);
				break;
			case 'p':
				Plane *plane = new Plane();
				read_plane(line.substr(2), *plane);
				break;
		}
	});
}

