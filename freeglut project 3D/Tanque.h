#pragma once

#include <GL/freeglut.h>
#include "Rueda.h"

class Tanque
{
public:
	Tanque(GLdouble longitud, GLdouble ancho, GLdouble alto);
	~Tanque();
	void dibuja();
	void aumentaAngulo(GLdouble valor);
	void giraRueda (GLdouble valor);

private:
	GLdouble longitud, ancho, alto, angulo, anguloRueda;
	Rueda rueda;
};

