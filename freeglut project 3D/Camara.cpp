#include "Camara.h"


Camara::Camara()
{
}


Camara::~Camara()
{
}


void Camara::setEye(PuntoVector3D * eye) {
	this->eye = eye;
}

void Camara::setLook(PuntoVector3D * look) {
	this->look = look;
}

void Camara::setUp(PuntoVector3D * up) {
	this->up = up;
}

void Camara::setDirect() {
	//n = (eye-look).normaliza
	//u = (look x n).norm
	//v = n x u
	//matrix = u v n e
	PuntoVector3D * n = this->eye->resta(this->look);
	n->normalizar();
	PuntoVector3D * u = this->look->productoVectorial(n);
	u->normalizar();
	PuntoVector3D * v = n->productoVectorial(u);
	GLfloat matrix[16];

	matrix[0] = u->getX();
	matrix[1] = u->getY();
	matrix[2] = u->getZ();
	matrix[3] = 0;
	matrix[4] = v->getX();
	matrix[5] = v->getY();
	matrix[6] = v->getZ();
	matrix[7] = 0;
	matrix[8] = n->getX();
	matrix[9] = n->getY();
	matrix[10] = n->getZ();
	matrix[11] = 0;
	matrix[12] = this->eye->getX();
	matrix[13] = this->eye->getY();
	matrix[14] = this->eye->getZ();
	matrix[15] = 1;

	glMultMatrixf(matrix);
}

void Camara::setInverse() {
	//n = (eye-look).normaliza
	//u = (look x n).norm
	//v = n x u
	//matrix = u v n e
	PuntoVector3D * n = this->eye->resta(this->look);
	n->normalizar();
	PuntoVector3D * u = this->up->productoVectorial(n);
	u->normalizar();
	PuntoVector3D * v = n->productoVectorial(u);
	GLfloat matrix[16];
	GLfloat eu = this->eye->productoEscalar(u);
	GLfloat en = this->eye->productoEscalar(n);
	GLfloat ev = this->eye->productoEscalar(v);

	matrix[0] = u->getX();
	matrix[1] = v->getX();
	matrix[2] = n->getX();
	matrix[3] = 0;
	matrix[4] = u->getY();
	matrix[5] = v->getY();
	matrix[6] = n->getY();
	matrix[7] = 0;
	matrix[8] = u->getZ();
	matrix[9] = v->getZ();
	matrix[10] = n->getZ();
	matrix[11] = 0;
	matrix[12] = -eu;
	matrix[13] = -ev;
	matrix[14] = -en;
	matrix[15] = 1;

	glMultMatrixf(matrix);
}