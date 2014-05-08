#include "stdafx.h"
#include "Drawer.h"
#include "Example1.h"
#include "RoomModel.h"
#include "Glass.h"
#include "BeerBottle.h"

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
	auto object1 = new RoomModel();
	this->objectsToDraw["room"] = object1;

	auto object2 = new Glass();
	this->objectsToDraw["glass"]=object2;

	auto object3 = new BeerBottle();
	this->objectsToDraw["beer"] = object3;
}

void Drawer::Display()
{

	//Wyczyszczenie okna
	glClearColor(0,0,0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Obliczenie macierzy rzutowania
	//kat widzenia , stosunek wymiarow okna,plaszczyzna odcinania bliska, daleka, 
	glm::mat4 P = glm::perspective(this->params->perspectiveAngle, 16.0f/9.0f, 1.0f, 150.0f);

	//Obliczenie macierzy widoku (de fact ustawienie kamery na scenie);
	glm::mat4 V = glm::lookAt(
		this->params->observer, //pozycja kamery
		this->params->center, //"CO JA PACZE"
		this->params->nose);
	this->PassMatrixesToAllObjects(&V, &P);

	//Za³adowanie macierzy rzutowania do OpenGL
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));

	//Przygotowanie do ³adowania macierzy widoku i modelu
	glMatrixMode(GL_MODELVIEW);
	
	
	
	//glLightfv(GL_LIGHT3,GL_AMBIENT,ambientColor);
	
	if(this->params->light3on)
		glEnable(GL_LIGHT3);
	else
		glDisable(GL_LIGHT3);
	this->objectsToDraw["room"]->Draw();
	this->objectsToDraw["glass"]->Draw();
	this->objectsToDraw["beer"]->Draw();

	//Przerzucenie tylnego bufora na przedni
	glutSwapBuffers();

	
}

void Drawer::PrepareNextFrame()
{
	this->objectsToDraw["room"]->NextFrame();
	glutPostRedisplay();
}

void Drawer::PassMatrixesToAllObjects(glm::mat4 *viewMatrix,glm::mat4 *pMatrix)
{
	for (auto it = this->objectsToDraw.begin(); it != this->objectsToDraw.end(); ++it)
	{
		it->second->SetMatrixes(viewMatrix, pMatrix);
	}
}