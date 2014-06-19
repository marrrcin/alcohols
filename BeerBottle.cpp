#include "BeerBottle.h"

BeerBottle::BeerBottle()
{

	this->QuickLoadFromFiles("beer");
	glm::mat4 *M = new glm::mat4(1.0f);
	*M = glm::scale(*M,glm::vec3(0.2f,0.2f,0.2f));
	*M = glm::translate(*M,glm::vec3(-8.35f,8.4f,-2.5f));
	*M = glm::translate(*M,glm::vec3(-7.75f,13.25f,-2.8f));

	this->modelMatrix = M;
}


BeerBottle::~BeerBottle()
{
	delete this->modelMatrix;
}

void BeerBottle::Draw()
{
	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(*V**this->modelMatrix)); //SYNTAX SHIT,I'm in a hurry, sorry
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0f, 1.0f, 1.0f);
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void BeerBottle::NextFrame()
{
	//

}