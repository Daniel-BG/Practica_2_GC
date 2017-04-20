#pragma once
#include "Malla.h"
class Cono :
	public Malla
{
public:
	Cono(int perfiles, int radio, int altura);
	virtual ~Cono();

private:
	int perfiles;
	int radio;
	int altura;
};

