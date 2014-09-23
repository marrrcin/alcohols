#include "Absinthe.h"

Absinthe::Absinthe()
{
	//this->LoadModelFromObjFile("absolut.obj");
	//this->ExportLoadedMatrixesToFile("absinthe");
	this->QuickLoadFromFiles("absinthe");
	this->flattenData();

	this->alcohol = new Alcohol(700, 80);
}


Absinthe::~Absinthe()
{
	delete this->modelMatrix;
}

void Absinthe::Draw()
{

	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glm::mat4 *M = new glm::mat4(1.0f);
	this->modelMatrix = M;
	*M = glm::scale(*M, glm::vec3(0.05f));
	*M = glm::scale(*M, glm::vec3(0.15f));
	*M = glm::scale(*M, glm::vec3(1.3f));
	*M = glm::translate(*M, glm::vec3(730.0f, 700.0f, 1000.0f));
	
	if (this->modelMover->isEnabled)
	{
	*M = this->modelMover->Scale(*M);
	*M = this->modelMover->Rotate(*M);
	*M = this->modelMover->Translate(*M);
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(*V**M));
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(101/255.0f, 143/255.0f, 128/255.0f);
	if (this->collisionDetected)
		glColor3f(1.0f, 0.0f, 0.0f);
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void Absinthe::NextFrame()
{

}