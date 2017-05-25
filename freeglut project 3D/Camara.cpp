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

void Camara::inside(CurvaHipotrocoide * curva, Tanque * tanque, float t) {
	PuntoVector3D * eye = curva->getC(t);
	//eye->sumar(tanque->getCannonOffset());
	this->setEye(eye);
	PuntoVector3D * look = curva->getC(t);
	look->sumar(curva->getC1(t));
	this->setLook(look);
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
	n = this->eye->resta(this->look);
	n->normalizar();
	u = this->up->productoVectorial(n);
	u->normalizar();
	v = n->productoVectorial(u);
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

void Camara::rotationX(GLfloat angle) {
	this->eye = this->eye->rotateAgainstNormal(new PuntoVector3D(1, 0, 0, 0), angle);
	this->setInverse();
}

void Camara::rotationY(GLfloat angle) {
	this->eye = this->eye->rotateAgainstNormal(new PuntoVector3D(0, 1, 0, 0), angle);
	this->setInverse();
}

void Camara::rotationZ(GLfloat angle) {
	this->eye = this->eye->rotateAgainstNormal(new PuntoVector3D(0, 0, 1, 0), angle);
	this->setInverse();
}

/*
El método este hace lo mismo que el rotationX, pero solo te permite rotar frente 
a la posicion inicial, por lo que es peor y por eso esta quitado

void Camara::rotationX2() {
	this->angle += 2.0f * PI / 100.0f;
	if (this->angle > 2.0f * PI) {
		this->angle -= 2.0f * PI;
		
	}
	this->setEye(new PuntoVector3D(this->eye->getX(), this->initialEye->getY() * cos(-this->angle), this->initialEye->getZ() * sin(-this->angle), 1));
}*/

/*--roll:
 *rotate up with respect to n
 */
void Camara::roll(GLfloat angle) {
	this->up = this->up->rotateAgainstNormal(this->n, angle);
	this->setInverse(); //recalculate v, u, n
}

/*--pitch:
 *rotate up with respect to u
 *rotate vec = (look - eye) with respect to u, new look is eye + rotated vec
 */
void Camara::pitch(GLfloat angle) {
	this->up = this->up->rotateAgainstNormal(this->u, angle);
	PuntoVector3D * vec = this->look->clonar();
	vec = vec->resta(this->eye);
	vec = vec->rotateAgainstNormal(this->u, angle);
	vec->sumar(this->eye);
	this->look = vec;

	this->setInverse(); //recalculate v, u, n
}


/*--yaw :
 *rotate up with respect to v(most likely unchanged)
 *rotate vec = (look - eye) with respect to v, new look is eye + rotated vec
 */
void Camara::yaw(GLfloat angle) {
	this->up = this->up->rotateAgainstNormal(this->v, angle);
	PuntoVector3D * vec = this->look->clonar();
	vec = vec->resta(this->eye);
	vec = vec->rotateAgainstNormal(this->v, angle);
	vec->sumar(this->eye);
	this->look = vec;

	this->setInverse(); //recalculate v, u, n
}



