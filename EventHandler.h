#pragma once
#include "EventParameters.h"
class EventHandler
{
private:
	float cameraSpeed;
	float mouseSpeed;

	float cameraYrange;
	float cameraXrange;

	int lastMouseX;
	int lastMouseY;

	int tmpDifference;

	float CalculateCameraZDifference(int deltaX,int windowWidth);
	void CalculateLookAtAngle();
	bool doneY;

	float toRad;
public:
	EventHandler();
	~EventHandler();

	void KeyDown(unsigned char c, int x, int y);
	void KeyUp(unsigned char c, int x, int y);

	void SpecialKeyDown(int c,int x,int y);
	void SpecialKeyUp(int c,int x,int y);
	
	void MouseMove(int x,int y);

	EventParameters *params;
};

