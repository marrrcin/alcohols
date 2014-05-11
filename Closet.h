#pragma once
#include "Model.h"
class Closet :
	public Model
{
public:
	Closet();
	~Closet();
	virtual void Draw();
	virtual void NextFrame();

};

