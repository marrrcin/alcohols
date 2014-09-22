#pragma once
#include "Model.h"
class Champagne :
	public Model
{
public:
	Champagne();
	~Champagne();
	virtual void Draw();
	virtual void NextFrame();
};

