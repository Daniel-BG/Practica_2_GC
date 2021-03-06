
#ifndef _PuntoVector3D_H_
#define _PuntoVector3D_H_

#include <math.h>
#include <GL/freeglut.h>
#include "Constants.h"
#include <iostream>

class PuntoVector3D {
	private:
		GLfloat x, y, z;
        int pv;
    public:
        PuntoVector3D(GLfloat x, GLfloat y, GLfloat z, int pv);
        ~PuntoVector3D();
        GLfloat getX();
        GLfloat getY();
        GLfloat getZ();
		GLfloat getNorm();
        bool esPunto();
        bool esVector();
        void escalar(GLfloat factor);
        void normalizar();
        void sumar(PuntoVector3D* pv);
		PuntoVector3D* resta(PuntoVector3D* pv);
        PuntoVector3D* clonar();
        GLfloat productoEscalar(PuntoVector3D* vector);
        PuntoVector3D* productoVectorial(PuntoVector3D* vector);

		PuntoVector3D* rotateAgainstNormal(PuntoVector3D* v, GLdouble angle);

		friend std::ostream& operator<< (std::ostream& stream, const PuntoVector3D& pvec) {
			stream << "(" << pvec.x << "," << pvec.y << "," << pvec.z << ";" << pvec.pv << ")";
			return stream;
		}
};
#endif

