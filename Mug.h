#pragma once
#include "Model.h"
class Mug :
	public Model
{
public:
	Mug();
	~Mug();
	virtual void Draw();
	virtual void NextFrame();
};

