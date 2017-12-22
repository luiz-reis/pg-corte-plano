#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include "Vetor.h"
#include "Scene.h"
#include "SDLReader.h"
#include "Camera.h"

void initialize(string file_object, string file_camera, string file_light, string file_plane);
void draw();
void key_press(unsigned char key, int x, int y);

int window;

Scene* scene;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                 	// Initialize GLUT
	glutInitWindowSize(800, 600);   		// Set the window's initial width & height
	glutInitWindowPosition(50, 50); 		// Position the window's initial top-left corner
	window = glutCreateWindow("OpenGL Setup Test"); 	// Create a window with the given title
	glutDisplayFunc(draw); 					// Register display callback handler for window re-paint
	glutKeyboardFunc(key_press);						//Register keyboard callback handler
	initialize(argv[1], argv[2], argv[3], argv[4]);
	glutMainLoop();           				// Enter the event-processing loop
	return 0;
}

void key_press(unsigned char key, int x, int y)
{
	switch(key) 
	{ 
		case 27: //esc press
			glutDestroyWindow(window);
			if(scene != nullptr)
				delete scene;
			exit(0);
		break;
	}
}

void initialize(string file_object, string file_camera, string file_light, string file_plane)
{
	scene = new Scene();
	SDLReader::read_sdl(*scene, file_object, file_camera, file_light, file_plane);
	
	int m_viewport[4];
	glGetIntegerv( GL_VIEWPORT, m_viewport);
	scene->get_camera()->set_screen_res(m_viewport[2], m_viewport[3]); //width x height
	scene->set_buffer(m_viewport[2], m_viewport[3]); //width x height
	scene->set_la(Color(100, 100, 100));
	scene->draw();
}

void draw()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
		
	Camera *camera = scene->get_camera();	
	glDrawPixels(camera->get_resx(), camera->get_resy(), GL_RGB, GL_FLOAT, scene->get_buffer());

	glFlush();
}







//g++-5 -std=c++11 -framework GLUT -framework OpenGL -framework Cocoa Vetor.cpp Matrix4.cpp Color.cpp Util.h Plane.cpp  Material.cpp Light.cpp Mesh.cpp Triangle.cpp Camera.cpp Scene.cpp SDLReader.cpp main.cpp -o main.out -w
