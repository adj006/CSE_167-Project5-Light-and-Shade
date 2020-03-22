#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "MatrixTransform.h"
#include <GL/glut.h>

class Light:public MatrixTransform
{
public:
	Light();
	Light(int l);
};

#endif