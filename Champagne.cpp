#include "Champagne.h"

Champagne::Champagne()
{
	//this->LoadModelFromObjFile("champagne.obj");
	//this->ExportLoadedMatrixesToFile("champagne");
	this->QuickLoadFromFiles("champagne");
	this->flattenData();

	this->alcohol = new Alcohol(700, 10);
}


Champagne::~Champagne()
{
	delete this->modelMatrix;
}

void Champagne::Draw()
{

	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glm::mat4 *M = new glm::mat4(1.0f);
	this->modelMatrix = M;
	*M = glm::scale(*M, glm::vec3(0.05f));
	*M = glm::scale(*M, glm::vec3(0.15f));

	
	if (this->modelMover->isEnabled)
	{
	*M = this->modelMover->Scale(*M);
	*M = this->modelMover->Rotate(*M);
	*M = this->modelMover->Translate(*M);
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(*V**M));
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0f, 1.0f, 0.0f);
	if (this->collisionDetected)
		glColor3f(1.0f, 0.0f, 0.0f);
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void Champagne::NextFrame()
{

}