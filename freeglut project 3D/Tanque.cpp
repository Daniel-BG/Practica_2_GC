#include "Tanque.h"


Tanque::Tanque(GLdouble longitud, GLdouble ancho, GLdouble alto) :
	longitud(longitud),
	ancho(ancho),
	alto(alto),
	angulo(0),
	anguloRueda(0),
	rueda(Rueda(longitud / 3, 3))
{
}


Tanque::~Tanque()
{
}


PuntoVector3D * Tanque::getCannonOffset() {
	float offset = longitud / 4 + longitud * 1.2;
	return new PuntoVector3D(offset * cos(angulo), longitud * 3 / 4, offset * sin(angulo), 1);
}

PuntoVector3D * Tanque::getCannonVector() {
	return new PuntoVector3D(cos(angulo), 0, sin(angulo), 0);
}

void Tanque::dibuja() {
	//glTranslate(longitud/2, );
	GLdouble sizeAbajo = longitud;
	GLdouble sizeArriba = longitud / 2;
	GLdouble radioCilindro = sizeArriba / 8;
	GLdouble longitudCilindro = longitud * 1.2;
	GLdouble radioRueda = longitud/3;
	GLdouble longitudRueda = longitud / 4;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(0.2, 0.8, 0.2);
	glutSolidCube(sizeAbajo);
	glTranslated(0, sizeAbajo / 2 + sizeArriba / 2, 0);
	glRotated(angulo, 0, 1, 0);
	glColor3f(0.1, 0.6, 0.1);
	glutSolidCube(sizeArriba);
	//Cañon
	glTranslated(sizeArriba/2, 0, 0);
	glRotated(90,0,1,0);
	glColor3f(0.1, 0.4, 0.1);
	glutSolidCylinder(radioCilindro, longitudCilindro,100,2);
	glRotated(-90, 0, 1, 0);
	glTranslated(-sizeArriba/2, 0, 0);
	glRotated(-angulo, 0, 1, 0);
	glTranslated(0, - (sizeAbajo / 2 + sizeArriba / 2), 0);
	//Ruedas
	glTranslated(sizeAbajo/2, -sizeAbajo/2 + 2* radioRueda / 3, sizeAbajo/2);
	rueda.dibuja(anguloRueda);
	glTranslated(-sizeAbajo, 0, 0);
	rueda.dibuja(anguloRueda);
	glTranslated(0,0,-sizeAbajo);
	glRotated(180, 0, 1, 0);
	rueda.dibuja(-anguloRueda);
	glTranslated(-sizeAbajo,0,0);
	rueda.dibuja(-anguloRueda);

	glPopMatrix();
}

void Tanque::aumentaAngulo(GLdouble valor) {
	angulo += valor;
}

void Tanque::giraRueda(GLdouble valor) {
	anguloRueda += valor;
}