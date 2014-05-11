#pragma once
#include "Model.h"
class BeerBottle :
	public Model
{
public:
	BeerBottle();
	~BeerBottle();
	virtual void Draw();
	virtual void NextFrame();
};

