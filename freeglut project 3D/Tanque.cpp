#include "Tanque.h"


Tanque::Tanque(GLdouble longitud, GLdouble ancho, GLdouble alto) :
	longitud(longitud),
	ancho(ancho),
	alto(alto),
	angulo(0),
	anguloRueda(0),
	rueda(Rueda(longitud / 3, 3))
{
	//light configuration
	GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 4.0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 4.0);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, white);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 4.0);
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
	GLdouble radioRueda = longitud / 3;
	GLdouble longitudRueda = longitud / 4;
	GLUquadricObj* q;
	q = gluNewQuadric();
	
	GLfloat dir[] = { 0.0, 0.0, 1.0 };
	GLfloat pos[] = { 0.0, 0.0, 0.0, 1.0f };

	//start!
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(0.2, 0.8, 0.2);
	glutSolidCube(sizeAbajo);
	//cilindros luces
	glTranslated(sizeAbajo / 2, 0, 0);
	glRotated(90, 0, 1, 0);
	glColor3f(0.1, 0.8, 0.1);
	glTranslated(-sizeAbajo / 3, 0, 0);
	//foco1
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
	glLightfv(GL_LIGHT1, GL_POSITION, pos);
	if (glIsEnabled(GL_LIGHT1)) {
		glDisable(GL_LIGHTING);
	}
	gluCylinder(q, radioCilindro, radioCilindro * 2, longitudCilindro / 6, 100, 1);
	//glutSolidCylinder(radioCilindro * 2, longitudCilindro / 6, 100, 2);
	if (glIsEnabled(GL_LIGHT1)) {
		glEnable(GL_LIGHTING);
	}
	glTranslated((sizeAbajo / 3) * 2, 0, 0);


	//foco 2
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);
	glLightfv(GL_LIGHT2, GL_POSITION, pos);
	if (glIsEnabled(GL_LIGHT2)) {
		glDisable(GL_LIGHTING);
	}
	gluCylinder(q, radioCilindro, radioCilindro * 2, longitudCilindro / 6, 100, 1);
	//glutSolidCylinder(radioCilindro * 2, longitudCilindro / 6, 100, 2);
	if (glIsEnabled(GL_LIGHT2)) {
		glEnable(GL_LIGHTING);
	}
	glTranslated(-sizeAbajo / 3, 0, 0);
	glRotated(-90, 0, 1, 0);
	glTranslated(-sizeAbajo / 2, 0, 0);
	//cubo arriba
	glPushMatrix();
	glTranslated(0, sizeAbajo / 2 + sizeArriba / 2, 0);
	glRotated(angulo, 0, 1, 0);
	glColor3f(0.1, 0.6, 0.1);
	glutSolidCube(sizeArriba);
	//Cañon
	glTranslated(sizeArriba / 2, 0, 0);
	glRotated(90, 0, 1, 0);
	glColor3f(0.1, 0.4, 0.1);
	//glutSolidCylinder(radioCilindro, glIsEnabled(GL_LIGHT3) ? longitudCilindro * 7 / 8 : longitudCilindro, 100, 2);
	if (glIsEnabled(GL_LIGHT3)) {
		glDisable(GL_LIGHTING);
	}
	glutSolidCylinder(radioCilindro, longitudCilindro, 100, 2);
	if (glIsEnabled(GL_LIGHT3)) {
		glEnable(GL_LIGHTING);
	}
	glTranslated(0, 0, longitudCilindro * 7 / 8);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir);
	glLightfv(GL_LIGHT3, GL_POSITION, pos);
	/*if (glIsEnabled(GL_LIGHT3)) {
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 0.2, 0.2);
		glutSolidCylinder(radioCilindro, longitudCilindro / 8, 100, 2);
		glEnable(GL_LIGHTING);
	}*/
	glPopMatrix();
	//Ruedas
	glTranslated(sizeAbajo / 2, -sizeAbajo / 2 + 2 * radioRueda / 3, sizeAbajo / 2);
	rueda.dibuja(anguloRueda);
	glTranslated(-sizeAbajo, 0, 0);
	rueda.dibuja(anguloRueda);
	glTranslated(0, 0, -sizeAbajo);
	glRotated(180, 0, 1, 0);
	rueda.dibuja(-anguloRueda);
	glTranslated(-sizeAbajo, 0, 0);
	rueda.dibuja(-anguloRueda);

	glPopMatrix();
	gluDeleteQuadric(q);
}

void Tanque::aumentaAngulo(GLdouble valor) {
	angulo += valor;
}

void Tanque::giraRueda(GLdouble valor) {
	anguloRueda += valor;
}

void Tanque::setLights(bool state) {
	lightsOn = state;
}