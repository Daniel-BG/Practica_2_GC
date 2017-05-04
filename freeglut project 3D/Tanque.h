#pragma once

#include <GL/freeglut.h>


class Tanque
{
public:
	Tanque(GLdouble longitud, GLdouble ancho, GLdouble alto);
	~Tanque();
	void dibuja();
	void aumentaAngulo(GLdouble valor);

private:
	GLdouble longitud, ancho, alto, angulo;

};

