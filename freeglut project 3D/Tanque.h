#pragma once

#include <GL/freeglut.h>
#include "Rueda.h"
#include "PuntoVector3D.h"

class Tanque
{
public:
	Tanque(GLdouble longitud, GLdouble ancho, GLdouble alto);
	~Tanque();
	void dibuja();
	void aumentaAngulo(GLdouble valor);
	void giraRueda (GLdouble valor);
	PuntoVector3D * getCannonOffset();
	PuntoVector3D * getCannonVector();
	void setLights(bool state);

private:
	GLdouble longitud, ancho, alto, angulo, anguloRueda;
	bool lightsOn = false;
	Rueda rueda;
};

