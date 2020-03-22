#ifndef _POINTCLOUD_H_
#define _POINTCLOUD_H_
#include "Geode.h"
#include "Vector3.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <sstream>
#include <vector>

using namespace std;

class PointCloud : public Geode
{
public:

	PointCloud();
	PointCloud(vector<float> p, vector<float> c, vector<float> n, vector<float> f, vector<float> fn);

	vector<float> position;
	vector<float> color;
	vector<float> normal;
	vector<float> face;
	vector<float> faceNormal;

	void render();
};

#endif