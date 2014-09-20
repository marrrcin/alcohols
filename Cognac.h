#pragma once
#include "Model.h"

class Cognac:
	public Model
{
public:
	Cognac();
	~Cognac();
	virtual void Draw();
	virtual void NextFrame();
};

