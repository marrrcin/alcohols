#pragma once
#include "Model.h"
class BeerBottle :
	public Model
{
private:
	float rotationAngle;
	float rotationSpeed;
	float lastTime;
	float startTime;
public:
	BeerBottle();
	~BeerBottle();
	virtual void Draw();
	virtual void NextFrame();
};

