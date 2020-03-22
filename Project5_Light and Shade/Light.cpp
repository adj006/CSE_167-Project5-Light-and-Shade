#include "Light.h"

Light::Light()
{

}

Light::Light(int l)
{
	if (l == 0)
	{
		GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	else if (l == 1)
	{
		GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
		//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);

		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
		GLfloat light1_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
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
	}

}
