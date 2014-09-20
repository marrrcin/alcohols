#include "BeerBottle.h"

BeerBottle::BeerBottle()
{

	this->QuickLoadFromFiles("beer");

	this->lastTime = 0;
	this->rotationAngle = 0;
	this->rotationSpeed = 140;

	this->alcohol = new Alcohol(500, 5);
}


BeerBottle::~BeerBottle()
{
	delete this->modelMatrix;
}

void BeerBottle::Draw()
{
	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glm::mat4 *M = new glm::mat4(1.0f);
	this->modelMatrix = M;

	*M = glm::scale(*M, glm::vec3(0.2f, 0.2f, 0.2f));
	*M = glm::translate(*M, glm::vec3(-8.35f, 8.4f, -2.5f));
	*M = glm::translate(*M, glm::vec3(-7.75f, 13.25f, -2.8f));

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(*V**M)); 

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0f, 1.0f, 1.0f);
	if (this->collisionDetected)
		glColor3f(1.0f, 0.0f, 0.0f);
	
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void BeerBottle::NextFrame()
{
	//

}
