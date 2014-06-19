#pragma once
#include "model.h"
class Lamp :
	public Model
{
private:
	float currentAngle;
	float speed;
	int lastTime;
public:
	Lamp(void);
	~Lamp(void);
	
	virtual void Draw();
	virtual void NextFrame();
};

