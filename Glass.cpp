#include "stdafx.h"
#include "Glass.h"


Glass::Glass()
{
	this->LoadModelFromObjFile("glass.obj");
}


Glass::~Glass()
{

}

void Glass::Draw()
{
	glm::mat4 *P = this->perspectiveMatrix;
	glm::mat4 *V = this->viewMatrix;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(*P));
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::scale(M,glm::vec3(3.0f));
	M = glm::rotate(M,90.0f,glm::vec3(0.0f,1.0f,0.0f));
	glLoadMatrixf(glm::value_ptr(*V*M));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glColor4f(199.0/255,201.0/255,254.0/255,0.9f);
	glDisable(GL_COLOR_MATERIAL);
	this->RenderObject();
	glDisable(GL_BLEND);
}

void Glass::NextFrame()
{

	//
}