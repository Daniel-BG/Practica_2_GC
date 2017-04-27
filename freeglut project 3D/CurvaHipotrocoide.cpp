#include "CurvaHipotrocoide.h"


CurvaHipotrocoide::CurvaHipotrocoide(float a, float b, float c):
a(a),
b(b),
c(c)
{
}


CurvaHipotrocoide::~CurvaHipotrocoide()
{
}


PuntoVector3D * CurvaHipotrocoide::getC(float t) {
	return new PuntoVector3D((a - b)*cos(t) + c*cos(t*((a - b) / b)), 0.0f, (a - b)*sin(t) - c*sin(t*((a - b) / b)), 1);
}

PuntoVector3D * CurvaHipotrocoide::getC1(float t) {
	return new PuntoVector3D(-(a - b)*sin(t) - c*sin(t*((a - b) / b))*((a - b) / b), 0.0f, (a - b)*cos(t) - c*cos(t*((a - b) / b))*((a - b) / b), 1);
}

PuntoVector3D * CurvaHipotrocoide::getC2(float t) {
	return new PuntoVector3D(-(a - b)*cos(t) - c*cos(t*((a - b) / b))*((a - b) / b)*((a - b) / b), 0.0f, -(a - b)*sin(t) + c*sin(t*((a - b) / b))*((a - b) / b)*((a - b) / b), 1);
}


PuntoVector3D * CurvaHipotrocoide::getN(float t) {
	PuntoVector3D * b = getB(t);
	PuntoVector3D * tt = getT(t);
	PuntoVector3D * res = b->productoVectorial(tt);
	res->normalizar();
	return res;
}

PuntoVector3D * CurvaHipotrocoide::getB(float t) {
	PuntoVector3D * c1 = getC1(t);
	PuntoVector3D * c2 = getC2(t);
	PuntoVector3D * res = c1->productoVectorial(c2);
	res->normalizar();
	return res;
}

PuntoVector3D * CurvaHipotrocoide::getT(float t) {
	PuntoVector3D * res = getC1(t);
	res->normalizar();
	return res;
}


