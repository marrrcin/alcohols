#pragma once
#include "model.h"
class BeerCan :
	public Model
{
public:
	BeerCan(void);
	~BeerCan(void);
	virtual void Draw();
	virtual void NextFrame();
};

