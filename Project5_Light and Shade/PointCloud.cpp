#include "PointCloud.h"

PointCloud::PointCloud()
{
	//position.clear();
	//color.clear();
	//normal.clear();
	//face.clear();
	//faceNormal.clear();
}

PointCloud::PointCloud(vector<float> p, vector<float> c, vector<float> n, vector<float> f, vector<float> fn)
{
	position = p;
	color = c;
	normal = n;
	face = f;
	faceNormal = fn;
}

void PointCloud::render()
{
	for (int x = 0; x < face.size(); x += 3)
	{
		//glColor3f(color[(face[x])], color[(face[x]) + 1], color[(face[x] * 3) + 2]);
		glColor3f(1, 1, 1);

		glNormal3d(normal[(faceNormal[x] - 1) * 3], normal[((faceNormal[x] - 1) * 3) + 1], normal[((faceNormal[x] - 1) * 3) + 2]);
		glVertex3d(position[(face[x] - 1) * 3], position[((face[x] - 1) * 3) + 1], position[((face[x] - 1) * 3) + 2]);

		glNormal3d(normal[(faceNormal[x + 1] - 1) * 3], normal[((faceNormal[x + 1] - 1) * 3) + 1], normal[((faceNormal[x + 1] - 1) * 3) + 2]);
		glVertex3d(position[(face[x + 1] - 1) * 3], position[((face[x + 1] - 1) * 3) + 1], position[((face[x + 1] - 1) * 3) + 2]);

		glNormal3d(normal[(faceNormal[x + 2] - 1) * 3], normal[((faceNormal[x + 2] - 1) * 3) + 1], normal[((faceNormal[x + 2] - 1) * 3) + 2]);
		glVertex3d(position[(face[x + 2] - 1) * 3], position[((face[x + 2] - 1) * 3) + 1], position[((face[x + 2] - 1) * 3) + 2]);
	}


}