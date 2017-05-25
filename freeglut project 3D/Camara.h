#pragma once
#include "PuntoVector3D.h"
#include "CurvaHipotrocoide.h"
#include "Tanque.h"
#include "Constants.h"


class Camara
{
private:
	PuntoVector3D * eye, * look, * up;

public:
	Camara();
	~Camara();

	void setEye(PuntoVector3D * eye);
	void setLook(PuntoVector3D * look);
	void setUp(PuntoVector3D * up);
	void setDirect();
	void setInverse();
	void inside(CurvaHipotrocoide * curva, Tanque * tanque, float t);
	void rotationX(GLfloat angle = 1.0f);
	void rotationY(GLfloat angle = 1.0f);
	void rotationZ(GLfloat angle = 1.0f);
};

