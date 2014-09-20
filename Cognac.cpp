#include "Cognac.h"


Cognac::Cognac()
{
	this->LoadModelFromObjFile("cognac.obj");
	this->ExportLoadedMatrixesToFile("cognac");
	this->alcohol = new Alcohol(700, 40);
	this->material = new MyMaterial("materials/cognac/");
}


Cognac::~Cognac()
{
	delete this->modelMatrix;
}

void Cognac::Draw()
{

	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glm::mat4 *M = new glm::mat4(1.0f);
	this->modelMatrix = M;
	*M = glm::scale(*M, glm::vec3(0.015f));
	*M = glm::scale(*M, glm::vec3(0.6f));
	*M = glm::translate(*M, glm::vec3(1.0f));
	*M = glm::translate(*M, glm::vec3(600.0, 350.0, 800.0));
	*M = glm::translate(*M, glm::vec3(0.0, 135.0, 197.0));

	if (this->modelMover->isEnabled)
	{
		*M = this->modelMover->Scale(*M);
		*M = this->modelMover->Rotate(*M);
		*M = this->modelMover->Translate(*M);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(*V**M));
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0f, 0.2f, 0.7f);
	if (this->collisionDetected)
		glColor3f(1.0f, 0.0f, 0.0f);
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void Cognac::NextFrame()
{

}