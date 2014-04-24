#include "stdafx.h"
#include "Drawer.h"
#include "Example1.h"


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
	auto object1 = new Example1();
	this->objectsToDraw["example1"] = object1;
}

void Drawer::Display()
{

	//Wyczyszczenie okna
	glClearColor(0.5, -0.5, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Obliczenie macierzy rzutowania
	glm::mat4 P = glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);

	//Obliczenie macierzy widoku (de fact ustawienie kamery na scenie);
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -30.0f), //pozycja kamery
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	this->PassMatrixesToAllObjects(&V, &P);


	//Za³adowanie macierzy rzutowania do OpenGL
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));

	//Przygotowanie do ³adowania macierzy widoku i modelu
	glMatrixMode(GL_MODELVIEW);
	this->objectsToDraw["example1"]->Draw();
	


	//Przerzucenie tylnego bufora na przedni
	glutSwapBuffers();
}

void Drawer::PrepareNextFrame()
{
	this->objectsToDraw["example1"]->NextFrame();
	glutPostRedisplay();
}

void Drawer::PassMatrixesToAllObjects(glm::mat4 *viewMatrix,glm::mat4 *pMatrix)
{
	for (auto it = this->objectsToDraw.begin(); it != this->objectsToDraw.end(); ++it)
	{
		it->second->SetMatrixes(viewMatrix, pMatrix);
	}
}