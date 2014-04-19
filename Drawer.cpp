#include "stdafx.h"
#include "Drawer.h"

Drawer::Drawer()
{

}


Drawer::~Drawer()
{
	for (auto it = this->objectsToDraw.begin(); it != this->objectsToDraw.end(); ++it)
	{
		delete (*it).second;
	}
}

void Drawer::CreateObjectsToDraw()
{
	this->objectsToDraw["example1"] = new Example1();
	auto g = (Example1*)objectsToDraw["example1"];
}

void Drawer::Display()
{

	//Wyczyszczenie okna
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->objectsToDraw["example1"]->Draw();
	


	//Przerzucenie tylnego bufora na przedni
	glutSwapBuffers();
}

void Drawer::PrepareNextFrame()
{
	this->objectsToDraw["example1"]->NextFrame();
	glutPostRedisplay();
}