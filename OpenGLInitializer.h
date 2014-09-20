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

	static void KeyDownEventHandler(unsigned char c, int x, int y)
	{
		self->events->KeyDown(c,x,y);
	}

	static void KeyUpEventHandler(unsigned char c, int x, int y)
	{
		self->events->KeyUp(c,x,y);
	}

	static void SpecialKeyUpEventHandler(int c,int x,int y)
	{
		self->events->SpecialKeyUp(c,x,y);
	}

	static void SpecialKeyDownEventHandler(int c,int x,int y)
	{
		self->events->SpecialKeyDown(c,x,y);	
	}

	static void MouseMove(int x,int y)
	{
		self->events->MouseMove(x,y);
	}

};

