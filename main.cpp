#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>

void draw();
void key_press(unsigned char key, int x, int y);

int window;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                 	// Initialize GLUT
	window = glutCreateWindow("OpenGL Setup Test"); 	// Create a window with the given title
	glutInitWindowSize(320, 320);   		// Set the window's initial width & height
	glutInitWindowPosition(50, 50); 		// Position the window's initial top-left corner
	glutDisplayFunc(draw); 					// Register display callback handler for window re-paint
	glutKeyboardFunc(key_press);						//Register keyboard callback handler
	glutMainLoop();           				// Enter the event-processing loop
	return 0;
}

void key_press(unsigned char key, int x, int y)
{
	switch(key) 
	{ 
		case 27: //esc press
			glutDestroyWindow(window);
			exit(0);
		break;
	}
}

void draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
 
	glFlush();
}

//g++-5 -framework GLUT -framework OpenGL -framework Cocoa Vetor.cpp main.cpp -o main.out