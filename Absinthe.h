#pragma once
#include "Model.h"

class Absinthe:
	public Model
{
public:
	Absinthe();
	~Absinthe();
	virtual void Draw();
	virtual void NextFrame();
};

