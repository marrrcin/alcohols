#include "WineBottle.h"

WineBottle::WineBottle()
{
	this->QuickLoadFromFiles("wineBottle");

	this->alcohol = new Alcohol(700, 15);
}


WineBottle::~WineBottle()
{
	delete this->modelMatrix;
}

void WineBottle::Draw()
{
	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glm::mat4 *M = new glm::mat4(1.0f);
	this->modelMatrix = M;

	*M = glm::scale(*M, glm::vec3(1.3f, 1.3f, 1.3f));
	*M = glm::translate(*M, glm::vec3(1.0f, 2.6f, 2.7f));

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
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void WineBottle::NextFrame()
{

}