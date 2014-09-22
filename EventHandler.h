#pragma once
#include "EventParameters.h"
#include <math.h>
#include <time.h>

class EventHandler
{
private:
	float cameraSpeed;
	float mouseSpeed;

	float cameraYrange;
	float cameraXrange;

	int lastMouseX;
	int lastMouseY;

	glm::vec3 temp;
	glm::vec3 temp2;

	float toRad;
	int difference;

	void UpdateMover(float value);
	bool CanMoveTo(glm::vec3 newPosition);

public:
	EventHandler();
	~EventHandler();

	void KeyDown(unsigned char c, int x, int y);
	void KeyUp(unsigned char c, int x, int y);

	void SpecialKeyDown(int c,int x,int y);
	void SpecialKeyUp(int c,int x,int y);
	
	void MouseMove(int x,int y);

	void SoberUp();
	EventParameters *params;
};

