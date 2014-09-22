// alcohols.cpp : Defines the entry point for the console application.
//

#include "alcohols.h"

using namespace std;


Lights *globalLights;
OpenGLInitializer* OpenGLInitializer::self;
int _tmain(int argc, char* argv[])
{
	OpenGLInitializer openGL;

	//glut init
	std::cout << "> Initializing GLUT..." << std::endl;
	openGL.Initialize(1024, 576, "Wirtualna galeria alkoholi", argc, argv);

	//lights
	std::cout << "> Initializing lights..." << std::endl;
	globalLights = new Lights();
	globalLights->addLight(6.11f, 5.0f, -4.92f, 1.0f, 1.0f, 1.0f, 40.0f, 1.0f);

	std::cout << "> Initializing Event Handler..." << std::endl;
	EventHandler *eventHandler = new EventHandler();
	EventParameters *eventParameters = new EventParameters();

	//obsluga klawiatury i myszki, pozycja kamery itp
	std::cout << "> Setting Event Handler..." << std::endl;
	eventHandler->params = eventParameters;
	openGL.SetEventHandler(eventHandler);

	//obsluz wszystkie zadeklarowane modele: 
	//wczytaj modele i ich materia³y z plików, zainicjuj obs³ugê kolizji i przypisz modelMover
	std::cout << "> Initializing Drawer..." << std::endl;
	Drawer *drawer = new Drawer(eventParameters);

	openGL.SetDrawer(drawer);

	// set up VBOs
	std::cout << "> Initializing VBOs..." << std::endl;
	openGL.setupVBO();

	//set up the VAO for a mesh
	std::cout << "> Initializing VAO..." << std::endl;
	openGL.setupVAO();

	//glut main loop
	std::cout << "> All done! Starting glut main loop!" << std::endl;
	openGL.StartMainLoop();


	delete drawer;
	delete eventHandler;
	delete eventParameters;
	return 0;
}

