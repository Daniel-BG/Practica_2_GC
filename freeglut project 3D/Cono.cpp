#include "Cono.h"


Cono::Cono(int perfiles, int radio, int altura) :
perfiles(perfiles),
radio(radio),
altura(altura)
{
	numeroVertices = perfiles + 1;
	vertice = new PuntoVector3D*[numeroVertices];
	numeroNormales = perfiles + 1;
	normal = new PuntoVector3D*[numeroNormales];
	numeroCaras = perfiles + 1;
	cara = new Cara*[numeroCaras];

	//crear puntos, normales y demás
	// Vértices  
	vertice[0] = new PuntoVector3D(0.0f, altura, 0.0f, 1);
	float angulo = 0;
	for (int i = 0; i < perfiles; i++, angulo += 2.0f*PI / (float)perfiles) {
		vertice[i+1] = new PuntoVector3D(radio*cos(angulo), 0.0f, radio*sin(angulo), 1);
	}
	
	// Normales  
	PuntoVector3D * c = vertice[0];
	for (int i = 0; i < perfiles; i++) {
		PuntoVector3D * a = vertice[i + 1];
		PuntoVector3D * b = vertice[1 + ((i + 1) % perfiles)];
		PuntoVector3D * v = c->resta(a);
		PuntoVector3D * w = b->resta(a);
		normal[i] = v->productoVectorial(w);
		normal[i]->normalizar();
	}
	normal[perfiles] = new PuntoVector3D(0.0f, -1.0f, 0.0f, 0);

	// Caras laterales
	VerticeNormal** aVN;

	for (int i = 0; i < perfiles; i++) {
		aVN = new VerticeNormal*[3];
		aVN[0] = new VerticeNormal(0, i);
		aVN[1] = new VerticeNormal(1 + ((i + 1) % perfiles), i);
		aVN[2] = new VerticeNormal(i + 1, i);
		cara[i] = new Cara(3, aVN);
	}

	// Cara de abajo
	aVN = new VerticeNormal*[perfiles];
	for (int i = 0; i < perfiles; i++) {
		aVN[i] = new VerticeNormal(i + 1, perfiles);
	}
	cara[perfiles] = new Cara(perfiles, aVN);
}


Cono::~Cono()
{
}
