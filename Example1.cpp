#include "stdafx.h"
#include "Example1.h"

Example1::Example1()
{
	this->LoadModelFromObjFile("window.obj");
	this->material.ambient[0]=0.0f;
	this->material.ambient[1]=0.0f;
	this->material.ambient[2]=0.0f;

	this->material.diffuse[0]=0.0f;
	this->material.diffuse[1]=0.61285f;
	this->material.diffuse[2]=0.8f;

	this->material.specular[0]=0.0f;
	this->material.specular[1]=0.0f;
	this->material.specular[2]=0.0f;

	this->material.shiness=96.078431f;
	this->material.dissolve=0.692064;
	this->material.opticalDensity=1.0f;
}


Example1::~Example1()
{
}


void Example1::Draw()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////==
//	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,this->material.ambient);
//	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->material.specular);
//	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&this->material.shiness);
//	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,this->material.diffuse);
//	glMaterialfv(GL_FRONT_AND_BACK,GL_ALPHA,&this->material.dissolve);
//
	/*  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
   GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
   GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat no_shininess[] = { 0.0 };
   GLfloat low_shininess[] = { 5.0 };
   GLfloat high_shininess[] = { 100.0 };
   GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

   glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable( GL_BLEND );
	//glMaterialfv(GL_FRONT_AND_BACK,
glEnable(GL_COLOR_MATERIAL);
glColor4f(1.0f,0.0f,0.0f,0.3f);
glDisable(GL_COLOR_MATERIAL);
   this->RenderObject();
   glDisable(GL_BLEND);
	//Przygotowanie do ³adowania macierzy widoku i modelu
	//glMatrixMode(GL_MODELVIEW);

	////Rysowanie obiektu (mozna to wykonaæ w pêtli dla wielu obiektów)
	////1. Wyliczenie jego macierzy modelu
	//glm::mat4 M = glm::mat4(1.0f);
	////2. Za³adowanie macierzy do OpenGL
	//glLoadMatrixf(glm::value_ptr(*this->viewMatrix*M));
	////3. Rysowanie obiektu
	//glColor3f(1, 0.5, 0.2);
	//glutSolidTorus(0.5, 1.5, 100, 100);

	////przesuniecie kuli (wzgedem torusa)
	////glm::mat4 M_sphere = glm::translate(glm::mat4(1.0f),glm::vec3(-1.5f,0.0f,0.0f));
	//////glm::mat4 M_sphere = glm::mat4(1.0f);
	////glm::mat4 M2 = glm::translate(M_sphere,glm::vec3(0.5f,0.0f,0.0f));
	////auto RotateSphere = glm::rotate(glm::mat4(1.0f),angle,glm::vec3(0.0f,1.0f,0.0f));
	//////glLoadMatrixf(glm::value_ptr(V*M*RotateSphere*M_sphere));
	////glLoadMatrixf(glm::value_ptr(V*M*M_sphere*RotateSphere));
	//glm::mat4 sphereM = glm::translate(M, glm::vec3(-1.5f, 0.0f, 0.0f));
	//glm::mat4 sphereM2 = glm::translate(sphereM, glm::vec3(0.5f, 0.0f, 0.0f));
	//glm::mat4 sphereRotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//glLoadMatrixf(glm::value_ptr(V*sphereM*sphereRotate*sphereM2));
	//glColor3f(0, 0, 1.0);
	//glutSolidSphere(2.0f, 100, 100);
}

void Example1::NextFrame()
{
//
}
