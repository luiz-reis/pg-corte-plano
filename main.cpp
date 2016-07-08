#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include "Vetor.h"
#include "Scene.h"
#include "SDLReader.h"
#include "Camera.h"

void initialize();
void draw();
void update();
void key_press(unsigned char key, int x, int y);

int window;

Scene* scene;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                 	// Initialize GLUT
	window = glutCreateWindow("OpenGL Setup Test"); 	// Create a window with the given title
	glutInitWindowSize(320, 320);   		// Set the window's initial width & height
	glutInitWindowPosition(50, 50); 		// Position the window's initial top-left corner
	glutDisplayFunc(draw); 					// Register display callback handler for window re-paint
	glutKeyboardFunc(key_press);						//Register keyboard callback handler
	initialize();
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

void rad_sdl(string a, Scene &b)
{
	
}

void initialize()
{
	scene = new Scene();
	SDLReader::read_sdl("arquivo.sdl", *scene);
	
	Camera *camera = new Camera(Vetor(0,0,-10),Vetor(0,1,0),Vetor(0,0,-1), 1, 100);
	glMatrixMode(GL_PROJECTION);
	//glLoadMatrixf(camera->get_projection());
	delete camera;
	
}

void draw_cube()
{
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	      // Top face (y = 1.0f)
	      // Define vertices in counter-clockwise (CCW) order with normal pointing out
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f( 1.0f, 1.0f, -1.0f);
	      glVertex3f(-1.0f, 1.0f, -1.0f);
	      glVertex3f(-1.0f, 1.0f,  1.0f);
	      glVertex3f( 1.0f, 1.0f,  1.0f);
 
	      // Bottom face (y = -1.0f)
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f( 1.0f, -1.0f,  1.0f);
	      glVertex3f(-1.0f, -1.0f,  1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f( 1.0f, -1.0f, -1.0f);
 
	      // Front face  (z = 1.0f)
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f( 1.0f,  1.0f, 1.0f);
	      glVertex3f(-1.0f,  1.0f, 1.0f);
	      glVertex3f(-1.0f, -1.0f, 1.0f);
	      glVertex3f( 1.0f, -1.0f, 1.0f);
 
	      // Back face (z = -1.0f)
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f( 1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f,  1.0f, -1.0f);
	      glVertex3f( 1.0f,  1.0f, -1.0f);
 
	      // Left face (x = -1.0f)
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f(-1.0f,  1.0f,  1.0f);
	      glVertex3f(-1.0f,  1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f,  1.0f);
 
	      // Right face (x = 1.0f)
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f(1.0f,  1.0f, -1.0f);
	      glVertex3f(1.0f,  1.0f,  1.0f);
	      glVertex3f(1.0f, -1.0f,  1.0f);
	      glVertex3f(1.0f, -1.0f, -1.0f);
	   glEnd();  // End of drawing color-cube
}

void draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	draw_cube();
 
	glFlush();
}


void update()
{
	
}







//g++-5 -std=c++11 -framework GLUT -framework OpenGL -framework Cocoa Vetor.cpp Matrix4.cpp Color.cpp Util.h Plane.cpp  Material.cpp Light.cpp Mesh.cpp Camera.cpp Scene.cpp SDLReader.cpp main.cpp -o main.out