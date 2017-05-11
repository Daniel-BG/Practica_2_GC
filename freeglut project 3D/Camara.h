#pragma once
#include "PuntoVector3D.h"

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
};

