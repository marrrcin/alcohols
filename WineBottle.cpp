#include "WineBottle.h"

WineBottle::WineBottle()
{
	this->QuickLoadFromFiles("wineBottle");

}


WineBottle::~WineBottle()
{
}

void WineBottle::Draw()
{
	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glm::mat4 M = glm::mat4(1.0f);

	M = glm::scale(M, glm::vec3(1.3f, 1.3f, 1.3f));
	M = glm::translate(M, glm::vec3(0, 1.6f, 1.7f));

	if (this->modelMover->isEnabled)
	{
		M = this->modelMover->Scale(M);
		M = this->modelMover->Rotate(M);
		M = this->modelMover->Translate(M);
	}

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0 / 255, 200.0 / 255, 0.0 / 255);

	M = glm::translate(M, glm::vec3(1.0f, 1.0f, 1.0f));

	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();

	glDisable(GL_COLOR_MATERIAL);
}

void WineBottle::NextFrame()
{

}