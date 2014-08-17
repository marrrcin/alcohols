#pragma once
#include "Model.h"
class WineBottle :
	public Model
{
public:
	WineBottle();
	~WineBottle();
	virtual void Draw();
	virtual void NextFrame();

};

