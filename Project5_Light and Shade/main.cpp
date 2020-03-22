#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "main.h"

using namespace std;

namespace Globals
{
	int bound = 0;
	Matrix4 m;
	int pointCloud = 0;
};

int main(int argc, char *argv[])
{
	Window::parser();

	//GLfloat specular[] = Window::specular;
	//GLfloat shininess[] = ;
	GLfloat position[] = { 0.0, 1.0, 10.0, 1.0 };	// lightsource position

	glutInit(&argc, argv);      	      	      // initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
	glutInitWindowSize(Window::width, Window::height);      // set initial window size
	glutCreateWindow("Project 5: Light and Shade");    	      // open window and set window title

	glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
	glEnable(GL_NORMALIZE);						// enable depth buffering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);



	// Generate light source:
	//glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//glDisable(GL_LIGHTING);

	
	GLfloat light_ambient[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 10.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHT0);
	//glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0, 1, 10);
	glColor3f(0, 0, 1);
	glLoadIdentity();
	glutSolidSphere(100, 10, 10);
	glPopMatrix();
	

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 3.0);

	
	GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	GLfloat light1_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { -2.0, 2.0, 17.0, 1.0 };
	//GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 5.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

	glEnable(GL_LIGHT1);
	//glDisable(GL_LIGHTING);
	

	/*
	//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCone(1.0, 5.0, 20, 20);
	//glPopMatrix();
	glFlush();
	*/

	Window::createPointCloud();

	// Install callback functions:
	glutKeyboardFunc(Window::processNormalKeys);
	//glutSpecialFunc(Window::specialKeysProcess);
	glutDisplayFunc(Window::displayCallback);
	glutReshapeFunc(Window::reshapeCallback);
	glutIdleFunc(Window::idleCallback);
	glutMouseFunc(Window::onMouseBtn);
	glutMotionFunc(Window::onMouseMove);

	glutMainLoop();
	return 0;
}

