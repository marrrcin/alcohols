#include "BeerBottle.h"

BeerBottle::BeerBottle()
{

	this->QuickLoadFromFiles("beer");
	
}


BeerBottle::~BeerBottle()
{
}

void BeerBottle::Draw()
{
	glm::mat4 *P = this->perspectiveMatrix;
	glm::mat4 *V = this->viewMatrix;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(*P));
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 M = glm::mat4(1.0f);
	if (this->modelMover->isEnabled)
	{
		M = this->modelMover->Scale(M);
		M = this->modelMover->Rotate(M);
		M = this->modelMover->Translate(M);
	}
	glLoadMatrixf(glm::value_ptr(*V*M));
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0f, 1.0f, 1.0f);
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void BeerBottle::NextFrame()
{
	//

}