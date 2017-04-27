#pragma once
#include "Malla.h"
#include "CurvaHipotrocoide.h"


class MallaExtrusion :
	public Malla
{
public:
	MallaExtrusion(int nP, int nQ, float r, float turns, CurvaHipotrocoide * c);
	virtual ~MallaExtrusion();
};

