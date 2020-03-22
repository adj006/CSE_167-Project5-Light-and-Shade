#include "Cube.h"

Cube::Cube()
{
	size = 0;
}

Cube::Cube(GLdouble cubeSize)
{
	size = cubeSize;
}

void Cube::render()
{
	glutSolidCube(size);
}
