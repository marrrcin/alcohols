#pragma once
#include "Model.h"
class Barrel :
	public Model
{
public:
	Barrel();
	~Barrel();
	virtual void Draw();
	virtual void NextFrame();
};

