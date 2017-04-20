 
#include "Cara.h"
 
Cara::Cara(int nV, VerticeNormal** aVN) {
	numeroVertices=nV;
    arrayVerticeNormal=aVN;
}

Cara::~Cara() {
    for (int i=0; i<numeroVertices; i++)
		delete arrayVerticeNormal[i];
    delete[] arrayVerticeNormal;
}

int Cara::getNumeroVertices() {
    return numeroVertices;
}

int Cara::getIndiceVerticeK(int k) {
    return arrayVerticeNormal[k]->getIV();
}

int Cara::getIndiceNormalK(int k) {
    return arrayVerticeNormal[k]->getIN();
}

 

