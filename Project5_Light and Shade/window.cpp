#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include <GL/glut.h>

#include "Window.h"

//Camera camera;

using namespace std;

int Window::width = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
GLfloat Window::specular[] = {0,0,0,0};
GLfloat Window::shininess[] = {0};
GLfloat Window::diffuse[] = {0,0,0,0};
int Window::perPixel = 0;

vector<float> positionBunny;
vector<float> normalBunny;
vector<float> colorBunny;
vector<float> faceBunny;
vector<float> faceNormalBunny;

vector<float> positionDragon;
vector<float> normalDragon;
vector<float> colorDragon;
vector<float> faceDragon;
vector<float> faceNormalDragon;


vector<float> positionBear;
vector<float> normalBear;
vector<float> colorBear;
vector<float> faceBear;
vector<float> faceNormalBear;

Vector3 maxBunny;
Vector3 minBunny;
Vector3 maxDragon;
Vector3 minDragon;
Vector3 maxBear;
Vector3 minBear;

Matrix4 ci;	//camera inverse matrix
//Matrix4 m;	//model Matrix
//MatrixTransform* root;
//MatrixTransform* child;
Matrix4 mScale;
Matrix4 mCreate;

Group * w = new Group();		//w group
Group * o = new Group();		//object group
Group * pLight = new Group();	//point light group
Group * sLight = new Group();	//spot light group

Vector3 e(0.0, 5.0, 30.0);	//center of projection
Vector3 up(0.0, 1.0, 0.0);	//up-vector
Vector3 d(0.0, 0.0, 0.0);	//look at

Camera camera(e, up, d);

//Robot* negro;

int dir = 0;

int spinNum = 1.0;
//int whichCamera = 1;
//int firstTime = 0;

Vector3 vec3;

//double legRot = 0;
//int frame = 0;
//int time = 0;
//int timebase = 0;
//double fps = 0;
//double dScale = 1;
//double dRot = 0;

int state = 0;
Vector3 lastPoint;
int pX = 0;
int pY = 0;

Matrix4 mScaleUp;
Matrix4 mScaleDown;
Matrix4 mRotLeft;
Matrix4 mRotRight;

void Window::parser()
{
	FILE* fp0;		// file pointer for bunny
	FILE* fp1;		// file pointer for dragon
	FILE* fp2;		// file pointer for bear
	float x, y, z;	// vertex coordinates
	float r, g, b;	// vertex color
	int c1, c2;		// characters read from file
	Vector3 tmpV3;

	fp0 = fopen("bunny.obj", "rb");
	if (fp0 == NULL) { cerr << "error loading file" << endl; exit(-1); }

	int numvb = 0;
	int numnb = 0;
	int numfb = 0;

	while (1)
	{
		c1 = fgetc(fp0);
		c2 = fgetc(fp0);

		if (c1 == EOF || c2 == EOF)
		{
			break;
		}

		else if ((c1 == 'v') && (c2 == ' '))
		{
			fscanf(fp0, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);

			positionBunny.push_back(x);
			positionBunny.push_back(y);
			positionBunny.push_back(z);
			//colorBunny.push_back(r);
			//colorBunny.push_back(g);
			//colorBunny.push_back(b);
			numvb++;
		}
		else if ((c1 == 'v') && (c2 == 'n'))
		{
			fscanf(fp0, "%f %f %f", &x, &y, &z);
			tmpV3.v3[0] = x;
			tmpV3.v3[1] = y;
			tmpV3.v3[2] = z;
			tmpV3.normalize();
			normalBunny.push_back(tmpV3.v3[0]);
			normalBunny.push_back(tmpV3.v3[1]);
			normalBunny.push_back(tmpV3.v3[2]);
			numnb++;
		}
		else if ((c1 == 'f') && (c2 == ' '))
		{
			fscanf(fp0, "%f//%f %f//%f %f//%f", &x, &y, &z, &r, &g, &b);

			faceBunny.push_back(x);
			faceNormalBunny.push_back(y);
			faceBunny.push_back(z);
			faceNormalBunny.push_back(r);
			faceBunny.push_back(g);
			faceNormalBunny.push_back(b);
			numfb++;
		}
	}
	fclose(fp0);
	cerr << "Num of bunny vertices: " << numvb << '\n';
	cerr << "Num of bunny normals: " << numnb << '\n';
	cerr << "Num of bunny faces: " << numfb << '\n';

	numvb = 0;
	numnb = 0;
	numfb = 0;

	maxBunny = getMax(0);
	minBunny = getMin(0);

	fp1 = fopen("dragon.obj", "rb");
	if (fp1 == NULL) { cerr << "error loading file" << endl; exit(-1); }

	while (1)
	{
		c1 = fgetc(fp1);
		c2 = fgetc(fp1);

		if (c1 == EOF || c2 == EOF)
		{
			break;
		}

		if ((c1 == 'v') && (c2 == ' '))
		{
			fscanf(fp1, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);

			positionDragon.push_back(x);
			positionDragon.push_back(y);
			positionDragon.push_back(z);
			//colorDragon.push_back(r);
			//colorDragon.push_back(g);
			//colorDragon.push_back(b);
			numvb++;
		}
		else if ((c1 == 'v') && (c2 == 'n'))
		{
			fscanf(fp1, "%f %f %f", &x, &y, &z);
			tmpV3.v3[0] = x;
			tmpV3.v3[1] = y;
			tmpV3.v3[2] = z;
			tmpV3.normalize();
			normalDragon.push_back(tmpV3.v3[0]);
			normalDragon.push_back(tmpV3.v3[1]);
			normalDragon.push_back(tmpV3.v3[2]);
			numnb++;
		}
		else if ((c1 == 'f') && (c2 == ' '))
		{
			fscanf(fp1, "%f//%f %f//%f %f//%f", &x, &y, &z, &r, &g, &b);

			faceDragon.push_back(x);
			faceNormalDragon.push_back(y);
			faceDragon.push_back(z);
			faceNormalDragon.push_back(r);
			faceDragon.push_back(g);
			faceNormalDragon.push_back(b);
			numfb++;
		}
		else
		{
			while (c2 != '\n' && c2 != EOF)
				c2 = fgetc(fp1);
		}
	}
	fclose(fp1);
	cerr << "Num of dragon vertices: " << numvb << '\n';
	cerr << "Num of dragon normals: " << numnb << '\n';
	cerr << "Num of dragon faces: " << numfb << '\n';

	numvb = 0;
	numnb = 0;
	numfb = 0;

	maxDragon = getMax(1);
	minDragon = getMin(1);

	fp2 = fopen("bear.obj", "rb");
	if (fp2 == NULL) { cerr << "error loading file" << endl; exit(-1); }

	while (1)
	{
		c1 = fgetc(fp2);
		c2 = fgetc(fp2);

		if (c1 == EOF || c2 == EOF)
		{
			break;
		}

		if ((c1 == 'v') && (c2 == ' '))
		{
			fscanf(fp2, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);

			positionBear.push_back(x);
			positionBear.push_back(y);
			positionBear.push_back(z);
			//colorBear.push_back(r);
			//colorBear.push_back(g);
			//colorBear.push_back(b);
			numvb++;
		}
		else if ((c1 == 'v') && (c2 == 'n'))
		{
			fscanf(fp2, "%f %f %f", &x, &y, &z);

			tmpV3.v3[0] = x;
			tmpV3.v3[1] = y;
			tmpV3.v3[2] = z;
			tmpV3.normalize();
			normalBear.push_back(tmpV3.v3[0]);
			normalBear.push_back(tmpV3.v3[1]);
			normalBear.push_back(tmpV3.v3[2]);
			numnb++;
		}
		else if ((c1 == 'f') && (c2 == ' '))
		{
			fscanf(fp2, "%f//%f %f//%f %f//%f", &x, &y, &z, &r, &g, &b);

			faceBear.push_back(x);
			faceNormalBear.push_back(y);
			faceBear.push_back(z);
			faceNormalBear.push_back(r);
			faceBear.push_back(g);
			faceNormalBear.push_back(b);
			numfb++;
		}
		else
		{
			while (c2 != '\n' && c2 != EOF)
				c2 = fgetc(fp2);
		}
	}
	fclose(fp2);
	cerr << "Num of bear vertices: " << numvb << '\n';
	cerr << "Num of bear normals: " << numnb << '\n';
	cerr << "Num of bear faces: " << numfb << '\n';

	numvb = 0;
	numnb = 0;
	numfb = 0;

	maxBear = getMax(2);
	minBear = getMin(2);

	Globals::m.identity();

	mScaleUp.identity();
	mScaleUp.makeScale(1.2, 1.2, 1.2);

	mScaleDown.identity();
	mScaleDown.makeScale(.8, .8, .8);

	mRotLeft.identity();
	mRotLeft.makeRotateY(2);

	mRotRight.identity();
	mRotRight.makeRotateY(-2);

	camera.inverse();
	ci = camera.cam;
	ci.print("camera inverse\n");
}

void Window::processNormalKeys(unsigned char key, int x, int y)
{
	//cout << "Hello" << endl;
	switch (key)
	{
	case 'x':
		//negro->iTransX -= 3;
		//cout << negro->iTransX << endl;
		break;
	case 'X':
		//negro->iTransX += 3;
		break;
	case 'y':
		///negro->iTransY -= 3;
		break;
	case 'Y':
		//negro->iTransY += 3;
		break;
	case 'z':
		//negro->iTransZ -= 3;
		break;
	case 'Z':
		//negro->iTransZ += 3;
		break;
	case 'r':
		//negro->iScale = 0;
		//negro->iTransX = 0;
		//negro->iTransY = 0;
		//negro->iTransZ = 0;
		//negro->rot = 0;
		break;
	case 's':
		//negro->iScale -= .2;
		//dScale -= .2;
		Globals::m = Globals::m * mScaleDown;
		break;
	case 'S':
		//negro->iScale += .2;
		//dScale += .2;
		Globals::m = Globals::m * mScaleUp;
		break;
	case 'm':
		//negro->rot -= 5;
		//dRot--;
		Globals::m = Globals::m * mRotRight;
		break;
	case 'M':
		//negro->rot += 5;
		//dRot++;
		Globals::m = Globals::m * mRotLeft;
		break;
	case '0':
		Globals::pointCloud = 0;
		createPointCloud();
		break;
	case '1':
		Globals::pointCloud = 1;
		createPointCloud();
		break;
	case '2':
		Globals::pointCloud = 2;
		createPointCloud();
		break;
	case 'p':
		if (Window::perPixel == 0)
			Window::perPixel = 1;
		else
			Window::perPixel = 0;
		createPointCloud();
		break;
	}

	//child->addChild(negro);
	//negro->update();
	//displayCallback();

}

/*
void Window::specialKeysProcess(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_F1:
		glutDisplayFunc(displayCallback_cube);
		glutIdleFunc(idleCallback_cube);
		break;
	case GLUT_KEY_F2:
		glutDisplayFunc(displayCallback_house);
		glutIdleFunc(idleCallback_house);
		whichCamera = 1;
		break;
	case GLUT_KEY_F3:
		glutDisplayFunc(displayCallback_house);
		glutIdleFunc(idleCallback_house);
		whichCamera = 2;
		break;
	case GLUT_KEY_F4:
		parser("Bunny.xyz");
		glutDisplayFunc(displayCallback_bunny);
		glutIdleFunc(idleCallback_bunny);
		firstTime = 1;
		getMin();
		getMax();

		break;
	case GLUT_KEY_F5:
		parser("Dragon.xyz");
		glutDisplayFunc(displayCallback_dragon);
		glutIdleFunc(idleCallback_dragon);
		firstTime = 1;
		getMin();
		getMax();

		break;
	}
}
*/

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	/*
	//cout << "idle" << endl;
	//cout << negro->rot << endl;
	if (dir == 0)
	{
		negro->rot++;
		if (negro->rot == 90)
			dir = 1;
	}
	else if (dir == 1)
	{
		negro->rot--;
		if (negro->rot == -90)
			dir = 0;
	}

	negro->update((negro->rot) / 2);
	*/

	displayCallback();         // call display routine to show the object
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
	cerr << "Window::reshapeCallback called" << endl;
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); // set perspective projection viewing frustum
	glTranslatef(0, 0, -30);    // move camera back 30 units so that it looks at the origin (or else it's in the origin)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	o->draw(Globals::m);

	// Generate material properties:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Window::specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Window::shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Window::diffuse);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnd();
	glFlush();
	glutSwapBuffers();
}

Vector3 Window::getMax(int pointCloud)

{

	Vector3 max;

	if (pointCloud == 0)
	{

		max.v3[0] = positionBunny[0];
							
		max.v3[1] = positionBunny[1];
							
		max.v3[2] = positionBunny[2];


		for (int i = 3; i < positionBunny.size() - 3; i += 3)

		{

			max.v3[0] = ((max.v3[0] > positionBunny[i]) ? max.v3[0] : positionBunny[i]);
											  
			max.v3[1] = ((max.v3[1] > positionBunny[i + 1]) ? max.v3[1] : positionBunny[i + 1]);
											  
			max.v3[2] = ((max.v3[2] > positionBunny[i + 2]) ? max.v3[2] : positionBunny[i + 2]);

		}

	}

	else if (pointCloud == 1)
	{

		max.v3[0] = positionDragon[0];
							
		max.v3[1] = positionDragon[1];
							
		max.v3[2] = positionDragon[2];


		for (int i = 3; i < positionDragon.size() - 3; i += 3)

		{

			max.v3[0] = ((max.v3[0] > positionDragon[i]) ? max.v3[0] : positionDragon[i]);
			
			max.v3[1] = ((max.v3[1] > positionDragon[i + 1]) ? max.v3[1] : positionDragon[i + 1]);
			
			max.v3[2] = ((max.v3[2] > positionDragon[i + 2]) ? max.v3[2] : positionDragon[i + 2]);

		}

	}

	else if (pointCloud == 2)
	{

		max.v3[0] = positionBear[0];
							
		max.v3[1] = positionBear[1];
							
		max.v3[2] = positionBear[2];


		for (int i = 3; i < positionBear.size() - 3; i += 3)

		{

			max.v3[0] = ((max.v3[0] > positionBear[i]) ? max.v3[0] : positionBear[i]);
											
			max.v3[1] = ((max.v3[1] > positionBear[i + 1]) ? max.v3[1] : positionBear[i + 1]);
											 
			max.v3[2] = ((max.v3[2] > positionBear[i + 2]) ? max.v3[2] : positionBear[i + 2]);

		}

	}


	max.print("Maximum Point Coordinates: ");

	return max;

}

Vector3 Window::getMin(int pointCloud)

{

	Vector3 min;

	if (pointCloud == 0)
	{

		min.v3[0] = positionBunny[0];
							
		min.v3[1] = positionBunny[1];
							
		min.v3[2] = positionBunny[2];

		for (int i = 3; i < positionBunny.size() - 3; i += 3)

		{

			min.v3[0] = ((min.v3[0] < positionBunny[i]) ? min.v3[0] : positionBunny[i]);

			min.v3[1] = ((min.v3[1] < positionBunny[i + 1]) ? min.v3[1] : positionBunny[i + 1]);

			min.v3[2] = ((min.v3[2] < positionBunny[i + 2]) ? min.v3[2] : positionBunny[i + 2]);

		}

	}

	else if (pointCloud == 1)
	{

		min.v3[0] = positionDragon[0];

		min.v3[1] = positionDragon[1];

		min.v3[2] = positionDragon[2];

		for (int i = 3; i < positionDragon.size() - 3; i += 3)
		{

			min.v3[0] = ((min.v3[0] < positionDragon[i]) ? min.v3[0] : positionDragon[i]);

			min.v3[1] = ((min.v3[1] < positionDragon[i + 1]) ? min.v3[1] : positionDragon[i + 1]);

			min.v3[2] = ((min.v3[2] < positionDragon[i + 2]) ? min.v3[2] : positionDragon[i + 2]);

		}

	}

	else if (pointCloud == 2)
	{

		min.v3[0] = positionBear[0];

		min.v3[1] = positionBear[1];

		min.v3[2] = positionBear[2];

		for (int i = 3; i < positionBear.size() - 3; i += 3)
		{

			min.v3[0] = ((min.v3[0] < positionBear[i]) ? min.v3[0] : positionBear[i]);

			min.v3[1] = ((min.v3[1] < positionBear[i + 1]) ? min.v3[1] : positionBear[i + 1]);

			min.v3[2] = ((min.v3[2] < positionBear[i + 2]) ? min.v3[2] : positionBear[i + 2]);

		}

	}


	min.print("Minimum Point Coordinates: ");

	return min;

}

void Window::createPointCloud()
{
	//camera.inverse();
	//ci = camera.cam;

	//mScale.identity();

	//mScale.makeScale(dScale, dScale, dScale);

	//Matrix4 mRot;
	//mRot.identity();

	//mRot.makeRotateY(dRot);

	mCreate.identity();

	//mCreate = mCreate * mScale;
	//mCreate = mCreate * mRot;

	w->addChild(o);
	o->children->clear();

	o->addChild(pLight);
	o->addChild(sLight);

	MatrixTransform * mtpLight = new MatrixTransform(mCreate);
	pLight->addChild(mtpLight);

	Matrix4 pLightTrans;
	pLightTrans.identity();

	pLightTrans.makeTranslate(0.0, 0.0, 15.0);

	pLightTrans = pLightTrans * mCreate;
	pLightTrans.print("Trans\n");

	MatrixTransform * mtpLightTrans = new MatrixTransform(pLightTrans);
	mtpLight->addChild(mtpLightTrans);

	mtpLightTrans->addChild(new Sphere(1, 10, 10));

	//pLight->draw(ci);

	//glutSolidSphere(1,10,10);

	//Matrix4 pLightScale;
	//pLightScale.identity();

	//pLightScale.makeScale(1, 1, 1);

	//MatrixTransform * mtpLightScale = new MatrixTransform(pLightScale);
	//pLight->addChild(mtpLightScale);


	//Sphere * spLight = new Sphere(1, 10, 10);

	//Light * light = new Light(0);
	
	//mtpLightTrans->addChild(light);

	//Matrix4 sLightTrans;
	//sLightTrans.identity();

	//sLightTrans.makeTranslate(-2.0, 2.0, 17.0);

	//Matrix4 sLightScale;
	//sLightScale.identity();

	//sLightScale.makeScale(1, 1, 1);

	//MatrixTransform * mtsLightScale = new MatrixTransform(sLightScale);
	//sLight->addChild(mtsLightScale);

	//MatrixTransform * mtsLightTrans = new MatrixTransform(sLightTrans);
	//mtsLightScale->addChild(mtsLightTrans);

	//Light * light1 = new Light(1);

	//mtsLightTrans->addChild(light1);

	//pLight->draw(light);


	if (Globals::pointCloud == 0)
	{
		Matrix4 transBunny;
		transBunny.identity();

		transBunny.makeTranslate(-(maxBunny.v3[0] + minBunny.v3[0]) / 2, -(maxBunny.v3[1] + minBunny.v3[1]) / 2, -(maxBunny.v3[2] + minBunny.v3[2]) / 2);

		Matrix4 scaleBunny;
		scaleBunny.identity();

		scaleBunny.makeScale((40 * tan(0.0174532925 * 30)) / (maxBunny.v3[0] - minBunny.v3[0]), (40 * tan(0.0174532925 * 30)) / (maxBunny.v3[1] - minBunny.v3[1]), (40 * tan(0.0174532925 * 30)) / (maxBunny.v3[2] - minBunny.v3[2]));

		MatrixTransform * mtScaleBunny = new MatrixTransform(scaleBunny);
		o->addChild(mtScaleBunny);

		MatrixTransform * mtTransBunny = new MatrixTransform(transBunny);
		mtScaleBunny->addChild(mtTransBunny);

		PointCloud * pcBunny = new PointCloud(positionBunny, colorBunny, normalBunny, faceBunny, faceNormalBunny);
		mtTransBunny->addChild(pcBunny);

		Window::specular[0] = 1.0;
		Window::specular[1] = 1.0;
		Window::specular[2] = 1.0;
		Window::specular[3] = 1.0;
		
		Window::shininess[0] = 100;
		
		Window::diffuse[0] = 0.0;
		Window::diffuse[1] = 0.0;
		Window::diffuse[2] = 0.0;
		Window::diffuse[3] = 0.0;
	}
	else if (Globals::pointCloud == 1)
	{
		Matrix4 transDragon;
		transDragon.identity();

		transDragon.makeTranslate(-(maxDragon.v3[0] + minDragon.v3[0]) / 2, -(maxDragon.v3[1] + minDragon.v3[1]) / 2, -(maxDragon.v3[2] + minDragon.v3[2]) / 2);

		Matrix4 scaleDragon;
		scaleDragon.identity();

		scaleDragon.makeScale((40 * tan(0.0174532925 * 30)) / (maxDragon.v3[0] - minDragon.v3[0]), (40 * tan(0.0174532925 * 30)) / (maxDragon.v3[1] - minDragon.v3[1]), (40 * tan(0.0174532925 * 30)) / (maxDragon.v3[2] - minDragon.v3[2]));

		MatrixTransform * mtScaleDragon = new MatrixTransform(scaleDragon);
		o->addChild(mtScaleDragon);

		MatrixTransform * mtTransDragon = new MatrixTransform(transDragon);
		mtScaleDragon->addChild(mtTransDragon);


		PointCloud * pcDragon = new PointCloud(positionDragon, colorDragon, normalDragon, faceDragon, faceNormalDragon);
		mtTransDragon->addChild(pcDragon);
		//mCreate = ci * mCreate;

		Window::specular[0] = 1.0;
		Window::specular[1] = 1.0;
		Window::specular[2] = 1.0;
		Window::specular[3] = 1.0;

		Window::shininess[0] = 25;

		Window::diffuse[0] = 0.0;
		Window::diffuse[1] = 0.0;
		Window::diffuse[2] = 0.0;
		Window::diffuse[3] = 0.0;
	}
	else if (Globals::pointCloud == 2)
	{
		Matrix4 transBear;
		transBear.identity();

		transBear.makeTranslate(-(maxBear.v3[0] + minBear.v3[0]) / 2, -(maxBear.v3[1] + minBear.v3[1]) / 2, -(maxBear.v3[2] + minBear.v3[2]) / 2);

		Matrix4 scaleBear;
		scaleBear.identity();

		scaleBear.makeScale((40 * tan(0.0174532925 * 30)) / (maxBear.v3[0] - minBear.v3[0]), (40 * tan(0.0174532925 * 30)) / (maxBear.v3[1] - minBear.v3[1]), (40 * tan(0.0174532925 * 30)) / (maxBear.v3[2] - minBear.v3[2]));

		MatrixTransform * mtScaleBear = new MatrixTransform(scaleBear);
		o->addChild(mtScaleBear);

		MatrixTransform * mtTransBear = new MatrixTransform(transBear);
		mtScaleBear->addChild(mtTransBear);

		PointCloud * pcBear = new PointCloud(positionBear, colorBear, normalBear, faceBear, faceNormalBear);
		mtTransBear->addChild(pcBear);
		//mCreate = ci * mCreate;

		Window::specular[0] = 1.0;
		Window::specular[1] = 1.0;
		Window::specular[2] = 1.0;
		Window::specular[3] = 1.0;

		Window::shininess[0] = 25;

		Window::diffuse[0] = 1.0;
		Window::diffuse[1] = 1.0;
		Window::diffuse[2] = 1.0;
		Window::diffuse[3] = 1.0;
	}
}

Vector3 Window::trackBallMapping(int x, int y)    // The CPoint class is a specific Windows class. Either use separate x and y values for the mouse location, or use a Vector3 in which you ignore the z coordinate.
{
	Vector3 v;    // Vector v is the synthesized 3D position of the mouse location on the trackball
	float d;     // this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
	v.v3[0] = (2.0*x - width) / width;   // this calculates the mouse X position in trackball coordinates, which range from -1 to +1
	v.v3[1] = (height - 2.0*y) / height;   // this does the equivalent to the above for the mouse Y position
	v.v3[2] = 0.0;   // initially the mouse z position is set to zero, but this will change below
	d = v.length();    // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
	d = (d<1.0) ? d : 1.0;   // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
	v.v3[2] = sqrtf(1.001 - d*d);  // this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
	v.normalize(); // Still need to normalize, since we only capped d, not v.
	return v;  // return the mouse location on the surface of the trackball
}

void Window::onMouseBtn(int btn, int s, int x, int y)
{

	//

	// Map the mouse position to a logical sphere location.

	// Keep it in the class variable lastPoint.

	//

	if (s == GLUT_DOWN)
	{
		pX = x;
		pY = y;
		lastPoint = trackBallMapping(x, y);

		if (btn == GLUT_LEFT_BUTTON)
			state = 1;
		else
			state = 2;
	}

	//

	// Make sure we are modifying the MODELVIEW matrix.

	//

	glMatrixMode(GL_MODELVIEW);

	//onMouseMove(x, y);

	cerr << "mouse clicked, points are : " << x << ", " << y << '\n';

	//createPointCloud();
}

void Window::onMouseMove(int x, int y)
{
	Vector3 dir;
	float rotAngle;
	float scaleFact;
	Vector3 point;
	double angle;
	Matrix4 rot;
	rot.identity();

	switch (state)
	{
	case 1:
		point = trackBallMapping(x, y);
		dir = dir.cross(point, lastPoint);
		dir.normalize();
		angle = dir.dot(point, lastPoint);
		rot.makeRotate(-angle, dir);
		Globals::m = rot * Globals::m;
		break;
	case 2:
		if (pY != y)
		{
			if (y < pY)
			{
				Globals::m = Globals::m * mScaleUp;
				cerr << "scaling up" << endl;
			}
			else if (y > pY)
			{
				
				Globals::m = Globals::m * mScaleDown;
				cerr << "scaling down" << endl;
			}
		}
		break;
	}
	cerr << "mouse moving, case: " << state << endl;
}


