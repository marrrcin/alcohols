#pragma once
#include "Model.h"
class Table :
	public Model
{
public:
	Table();
	~Table();
	virtual void Draw();
	virtual void NextFrame();
};

