#include "Rueda.h"


Rueda::Rueda(GLdouble radio, int slices):
radio(radio),
slices(slices)
{
	llanta = gluNewQuadric();
	neumatico = gluNewQuadric();
}


Rueda::~Rueda()
{
	gluDeleteQuadric(llanta);
	gluDeleteQuadric(neumatico);
}


void Rueda::dibuja(GLdouble anguloRueda) {
	glColor3d(0.0,0.0,0.0);
	glRotated(anguloRueda, 0,0,1);
	gluCylinder(neumatico, radio, radio, radio, slices, 1);
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(0,0,radio);
	gluDisk(neumatico, 0, radio, slices, 1);
	glTranslated(0,0,-radio);
	glRotated(-anguloRueda, 0, 0, 1);
}