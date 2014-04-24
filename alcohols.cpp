// alcohols.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Drawer.h"
#include "OpenGLInitializer.h"



using namespace std;



OpenGLInitializer* OpenGLInitializer::self;
int _tmain(int argc, char* argv[])
{
	OpenGLInitializer openGL;
	openGL.Initialize(1024, 576, "Wirtualna galeria alkoholi", argc, argv);

	Drawer *drawer = new Drawer();
	openGL.SetDrawer(drawer);

	EventHandler *eventHandler = new EventHandler();
	EventParameters *eventParameters = new EventParameters();
	eventHandler->params=eventParameters;
	drawer->params=eventParameters;
	openGL.SetEventHandler(eventHandler);





	openGL.StartMainLoop();


	delete drawer;
	delete eventHandler;
	delete eventParameters;
	return 0;
}

