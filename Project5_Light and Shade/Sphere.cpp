#include "Sphere.h"

Sphere::Sphere()
{
	radius = 0;
	slices = 0;
	stacks = 0;
}

Sphere::Sphere(GLdouble sRadius, GLint sSlices, GLint sStacks)
{
	radius = sRadius;
	slices = sSlices;
	stacks = sStacks;
}

void Sphere::render()
{
	glutSolidSphere(radius, slices, stacks);
}
