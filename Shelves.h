#pragma once
#include "model.h"
class Shelves : public Model
{
public:
	Shelves(void);
	~Shelves(void);

	virtual void Draw();
	virtual void NextFrame();
};

