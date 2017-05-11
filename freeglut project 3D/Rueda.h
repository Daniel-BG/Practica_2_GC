#pragma once

#include <GL/freeglut.h>

class Rueda
{
public:
	Rueda(GLdouble radio, int slices);
	~Rueda();
	void dibuja(GLdouble anguloRueda);

private:
	GLdouble radio;
	int slices;
	GLUquadricObj * llanta, * neumatico;

};

