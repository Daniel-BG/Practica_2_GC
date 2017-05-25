#pragma once
#include "PuntoVector3D.h"
#include "CurvaHipotrocoide.h"
#include "Tanque.h"

#define PI 3.14159265359f

class Camara
{
private:
	PuntoVector3D * eye, * look, * up, *initialEye;
	GLfloat angle;

public:
	Camara();
	~Camara();

	void setEye(PuntoVector3D * eye);
	void setLook(PuntoVector3D * look);
	void setUp(PuntoVector3D * up);
	void setDirect();
	void setInverse();
	void inside(CurvaHipotrocoide * curva, Tanque * tanque, float t);
	void rotationX(GLfloat radio = 1.0f);
};

