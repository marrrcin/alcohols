#pragma once
#include "Model.h"

class Vodka:
	public Model
{
public:
	Vodka();
	~Vodka();
	virtual void Draw();
	virtual void NextFrame();
};

