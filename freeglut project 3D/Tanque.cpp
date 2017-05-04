#include "Tanque.h"


Tanque::Tanque(GLdouble longitud, GLdouble ancho, GLdouble alto) :
	longitud(longitud),
	ancho(ancho),
	alto(alto),
	angulo(0)
{
}


Tanque::~Tanque()
{
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
	glColor3f(0.5, 1, 0.5);
	glutSolidCube(sizeAbajo);
	glTranslated(0, sizeAbajo / 2 + sizeArriba / 2, 0);
	glRotated(angulo, 0, 1, 0);
	glutSolidCube(sizeArriba);
	//Cañon
	glTranslated(sizeArriba/2, 0, 0);
	glRotated(90,0,1,0);
	glutSolidCylinder(radioCilindro, longitudCilindro,100,2);
	glRotated(-90, 0, 1, 0);
	glTranslated(-sizeArriba/2, 0, 0);
	glRotated(-angulo, 0, 1, 0);
	glTranslated(0, - (sizeAbajo / 2 + sizeArriba / 2), 0);
	//Ruedas
	glTranslated(sizeAbajo/2, -sizeAbajo/2 + 2* radioRueda / 3, sizeAbajo/2);
	glutSolidCylinder(radioRueda, longitudRueda, 100, 2);
	glTranslated(-sizeAbajo, 0, 0);
	glutSolidCylinder(radioRueda, longitudRueda, 100, 2);
	glTranslated(0,0,-sizeAbajo - longitudRueda);
	glutSolidCylinder(radioRueda, longitudRueda, 100, 2);
	glTranslated(sizeAbajo,0,0);
	glutSolidCylinder(radioRueda, longitudRueda, 100, 2);

	glPopMatrix();
}

void Tanque::aumentaAngulo(GLdouble valor) {
	angulo += valor;
}
