#pragma once
#include "PuntoVector3D.h"
class CurvaHipotrocoide
{
public:
	CurvaHipotrocoide(float a, float b, float c);
	~CurvaHipotrocoide();

	PuntoVector3D * getC(float t);
	PuntoVector3D * getN(float t);
	PuntoVector3D * getB(float t);
	PuntoVector3D * getT(float t);


	PuntoVector3D * getC1(float t);
	PuntoVector3D * getC2(float t);

private:
	float a, b, c;

};

