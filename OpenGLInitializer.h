#pragma once
#include <string>
#include "Drawer.h"
#include "EventHandler.h"
class OpenGLInitializer
{
private:
	Drawer* drawer;
	EventHandler* events;

public:
	
	OpenGLInitializer();
	~OpenGLInitializer();
	static OpenGLInitializer* self;
	bool Initialize(int screenWidth, int screenHeight, std::string title, int argc, char *argv[]);
	void SetDrawer(Drawer *drawer);
	void SetEventHandler(EventHandler *eventHandler);

	void StartMainLoop();

	static void DisplayFunction()
	{
		self->drawer->Display();
	}

	static void IdleFunction()
	{
		self->drawer->PrepareNextFrame();
	}

	static void KeyDownEventHandler(int c, int x, int y)
	{
		self->events->KeyDown(c,x,y);
	}

	static void KeyUpEventHandler(int c, int x, int y)
	{
		self->events->KeyUp(c,x,y);
	}
};

