#include "MallaExtrusion.h"


MallaExtrusion::MallaExtrusion(int nP, int nQ, float r, float turns, CurvaHipotrocoide * c)
{
	PuntoVector3D ** perfil = new PuntoVector3D*[nP];
	GLfloat matrix[16];

	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1;

	numeroVertices = nP*nQ;
	numeroCaras = (nP)*(nQ - 1);
	numeroNormales = numeroCaras;
	//Creación de los arrays
	vertice = new PuntoVector3D*[numeroVertices];
	normal = new PuntoVector3D*[numeroNormales];
	cara = new Cara*[numeroCaras];


	float t = 0;
	float inc = (2 * PI / nP);
	for (int i = 0; i < nP; i++) {
		perfil[i] = new PuntoVector3D(r*cos(i*inc), r*sin(i*inc), 0, 1);
	}


	//para cada traslación del polígono inicial
	inc = (2 * PI * turns / nQ);
	for (int i = 0; i < nQ; i++, t += inc) {
		PuntoVector3D * vn = c->getN(t);
		PuntoVector3D * vb = c->getB(t);
		PuntoVector3D * vt = c->getT(t);
		PuntoVector3D * pc = c->getC(t);
		matrix[0] = vn->getX();
		matrix[1] = vb->getX();
		matrix[2] = vt->getX();
		matrix[3] = pc->getX();
		matrix[4] = vn->getY();
		matrix[5] = vb->getY();
		matrix[6] = vt->getY();
		matrix[7] = pc->getY();
		matrix[8] = vn->getZ();
		matrix[9] = vb->getZ();
		matrix[10] = vt->getZ();
		matrix[11] = pc->getZ();



		//para cada punto del polígono inicial
		PuntoVector3D * proyection;
		for (int j = 0; j < nP; j++) {
			//multiplicar cada punto por la matriz y asignarlo al vector de puntos
			float px, py, pz;
			px = matrix[0] * perfil[j]->getX() + matrix[1] * perfil[j]->getY() + matrix[2] * perfil[j]->getZ() + matrix[3];
			py = matrix[4] * perfil[j]->getX() + matrix[5] * perfil[j]->getY() + matrix[6] * perfil[j]->getZ() + matrix[7];
			pz = matrix[8] * perfil[j]->getX() + matrix[9] * perfil[j]->getY() + matrix[10] * perfil[j]->getZ() + matrix[11];
			vertice[i * nP + j] = new PuntoVector3D(px, py, pz, 1);
		}
	}

	
	VerticeNormal** aVN;
	for (int i = 0; i < nQ - 1; i++) {
		for (int j = 0; j < nP; j++) {
			// Caras laterales
			aVN = new VerticeNormal*[4];
			aVN[0] = new VerticeNormal(i*nP + j, i*nP + j);
			aVN[1] = new VerticeNormal(i*nP + ((j + 1) % nP), i*nP + j);
			aVN[2] = new VerticeNormal((i + 1)*nP + ((j + 1) % nP), i*nP + j);
			aVN[3] = new VerticeNormal((i + 1)*nP + j, i*nP + j);
			cara[i*nP + j] = new Cara(4, aVN);
			normal[i*nP + j] = this->CalculoVectorNormalPorNewell(cara[i*nP + j]);
		}
	}




	delete[] perfil;
}


MallaExtrusion::~MallaExtrusion()
{
}
