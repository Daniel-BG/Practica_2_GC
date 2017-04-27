#pragma once
#include "Malla.h"
#include "CurvaHipotrocoide.h"


class MallaExtrusion :
	public Malla
{
public:
	MallaExtrusion(int nP, int nQ, float r, CurvaHipotrocoide * c);
	virtual ~MallaExtrusion();
};

