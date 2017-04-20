#include "FalsoTetraedro.h"
 
FalsoTetraedro::FalsoTetraedro() {
	numeroVertices=4;
	vertice=new PuntoVector3D*[numeroVertices];
    numeroNormales=4;
	normal=new PuntoVector3D*[numeroNormales];
    numeroCaras=4;
    cara=new Cara*[numeroCaras];
    modo=false;

	// Vértices  
	vertice[0]=new PuntoVector3D(0.0f, 0.0f, 0.0f, 1);
	vertice[1]=new PuntoVector3D(10.0f, 0.0f, 0.0f, 1);
	vertice[2]=new PuntoVector3D(0.0f, 10.0f, 0.0f, 1);
	vertice[3]=new PuntoVector3D(0.0f, 0.0f, 10.0f, 1);
	
	// Normales  
	normal[0]=new PuntoVector3D(0.577f, 0.577f, 0.577f, 0);
	normal[1]=new PuntoVector3D(0.0f, 0.0f, -1.0f, 0);	 
	normal[2]=new PuntoVector3D(-1.0f, 0.0f, 0.0f, 0);
	normal[3]=new PuntoVector3D(0.0f, -1.0f, 0.0f, 0);
	 
	// Caras
	VerticeNormal** aVN=new VerticeNormal*[3];

	aVN[0]=new VerticeNormal(1, 0);
	aVN[1]=new VerticeNormal(2, 0);
	aVN[2]=new VerticeNormal(3, 0);
	cara[0]=new Cara(3, aVN);

	aVN=new VerticeNormal*[3];
	aVN[0]=new VerticeNormal(0, 1);
	aVN[1]=new VerticeNormal(2, 1);
	aVN[2]=new VerticeNormal(1, 1);
	cara[1]=new Cara(3, aVN);

	aVN=new VerticeNormal*[3];
	aVN[0]=new VerticeNormal(0, 2);
	aVN[1]=new VerticeNormal(3, 2);
	aVN[2]=new VerticeNormal(2, 2);
	cara[2]=new Cara(3, aVN);

	aVN=new VerticeNormal*[3];
	aVN[0]=new VerticeNormal(0, 3);
	aVN[1]=new VerticeNormal(1, 3);
	aVN[2]=new VerticeNormal(3, 3);
	cara[3]=new Cara(3, aVN); 
}

FalsoTetraedro::~FalsoTetraedro() {
    for (int i=0; i<numeroVertices; i++)
        delete vertice[i];
    delete[] vertice;

    for (int i=0; i<numeroNormales; i++)
        delete normal[i];
    delete[] normal;

    for (int i=0; i<numeroCaras; i++)
        delete cara[i];
    delete[] cara;
}

void FalsoTetraedro::dibuja() {	 	 	 
	for (int i=0; i<numeroCaras; i++) {		
		if (!modo) glBegin(GL_POLYGON);
		else glBegin(GL_LINE_LOOP);
		if (i==0) glColor3f(1.0f, 1.0f, 1.0f);
		if (i==1) glColor3f(0.0f, 0.0f, 1.0f);
		if (i==2) glColor3f(1.0f, 0.0f, 0.0f);
		if (i==3) glColor3f(0.0f, 1.0f, 0.0f);
		for (int j=0; j<cara[i]->getNumeroVertices(); j++) {
			int iN=cara[i]->getIndiceNormalK(j);
			int iV=cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());            				 
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
}


 