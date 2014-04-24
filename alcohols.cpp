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
	openGL.Initialize(800, 600, "Wirtualna galeria alkoholi", argc, argv);
	Drawer *drawer = new Drawer();

	openGL.SetDrawer(drawer);





	openGL.StartMainLoop();


	delete drawer;
	
	return 0;
}

