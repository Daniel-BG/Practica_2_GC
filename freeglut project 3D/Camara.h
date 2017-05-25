#pragma once
#include "PuntoVector3D.h"
#include "CurvaHipotrocoide.h"
#include "Tanque.h"
#include "Constants.h"
#include <iostream>


class Camara
{
private:
	PuntoVector3D * eye, * look, * up, *initialEye;
	PuntoVector3D * n, * v, * u;
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

	void rotationX(GLfloat angle = 1.0f);
	void rotationY(GLfloat angle = 1.0f);
	void rotationZ(GLfloat angle = 1.0f);

	void roll(GLfloat angle = 1.0f);
	void pitch(GLfloat angle = 1.0f);
	void yaw(GLfloat angle = 1.0f);


};

