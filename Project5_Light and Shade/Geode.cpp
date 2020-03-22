#include "Geode.h"

void Geode::draw(Matrix4 c)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	c.transpose();
	//c.print("Camera Inverse Geode\n");
	glLoadMatrixd(c.getPointer());
	glBegin(GL_TRIANGLES);
	render();
}
