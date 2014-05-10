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

	/*
	w EventParameters s¹ wszystkie parametry, typu pozycja kamery;
	z t¹ klas¹ ³¹czy siê eventHandler, który obs³uguje klawiaturê i mysz,
	a co za tym idzie - modyfikuje parametry w eventParameters.

	eventParameters jest przekazywany do "drawera", który podczas rysowania
	odczytuje odpowiednie pola i ot i ca³a historyja.
	*/
	EventHandler *eventHandler = new EventHandler();
	EventParameters *eventParameters = new EventParameters();
	eventHandler->params = eventParameters;
	openGL.SetEventHandler(eventHandler);

	Drawer *drawer = new Drawer();
	drawer->params = eventParameters;
	openGL.SetDrawer(drawer);

	
	
	


	openGL.StartMainLoop();


	delete drawer;
	delete eventHandler;
	delete eventParameters;
	return 0;
}

