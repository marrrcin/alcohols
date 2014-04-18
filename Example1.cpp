#include "stdafx.h"
#include "Example1.h"


Example1::Example1()
{
}


Example1::~Example1()
{
}

void Example1::Draw()
{
	//Obliczenie macierzy rzutowania
	glm::mat4 P = glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);

	//Obliczenie macierzy widoku (de fact ustawienie kamery na scenie);
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 1.0f, -7.0f), //pozycja kamery
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	//Za�adowanie macierzy rzutowania do OpenGL
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));

	//Przygotowanie do �adowania macierzy widoku i modelu
	glMatrixMode(GL_MODELVIEW);


	//Rysowanie obiektu (mozna to wykona� w p�tli dla wielu obiekt�w)
	//1. Wyliczenie jego macierzy modelu
	glm::mat4 M = glm::rotate(glm::mat4(1.0f),angle, glm::vec3(1.0f, 0.0f, 0.0f));
	//2. Za�adowanie macierzy do OpenGL
	glLoadMatrixf(glm::value_ptr(V*M));
	//3. Rysowanie obiektu
	glColor3f(1, 0.5, 0.2);
	glutSolidTorus(0.5, 1.5, 100, 100);

	//przesuniecie kuli (wzgedem torusa)
	//glm::mat4 M_sphere = glm::translate(glm::mat4(1.0f),glm::vec3(-1.5f,0.0f,0.0f));
	////glm::mat4 M_sphere = glm::mat4(1.0f);
	//glm::mat4 M2 = glm::translate(M_sphere,glm::vec3(0.5f,0.0f,0.0f));
	//auto RotateSphere = glm::rotate(glm::mat4(1.0f),angle,glm::vec3(0.0f,1.0f,0.0f));
	////glLoadMatrixf(glm::value_ptr(V*M*RotateSphere*M_sphere));
	//glLoadMatrixf(glm::value_ptr(V*M*M_sphere*RotateSphere));
	glm::mat4 sphereM = glm::translate(M, glm::vec3(-1.5f, 0.0f, 0.0f));
	glm::mat4 sphereM2 = glm::translate(sphereM, glm::vec3(0.5f, 0.0f, 0.0f));
	glm::mat4 sphereRotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(V*sphereM*sphereRotate*sphereM2));
	glColor3f(0, 0, 1.0);
	glutSolidSphere(0.5f, 100, 100);
}

void Example1::NextFrame()
{
	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;
	angle += speed*interval / 1000.0;
	if (angle>360) angle -= 360;
	
}
