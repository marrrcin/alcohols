#pragma once
#include "Model.h"
class Glass : public Model
{
public:
	Glass();
	~Glass();

	virtual void Draw();
	virtual void NextFrame();
};

