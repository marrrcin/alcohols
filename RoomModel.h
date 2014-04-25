#pragma once
#include "Model.h"

class RoomModel : public Model
{
private:
	float angle;
	float speed;
	int lastTime;


	

public:
	RoomModel();
	~RoomModel();
	virtual void Draw();
	virtual void NextFrame();
};

