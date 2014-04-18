#pragma once
#include "Model.h"
class Example1 : public Model
{
private:
	float angle = 0;
	float speed = 180;
	int lastTime = 0;

public:
	Example1();
	~Example1();
	virtual void Draw();
	virtual void NextFrame();

};

