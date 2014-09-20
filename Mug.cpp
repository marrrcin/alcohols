#include "Mug.h"


Mug::Mug()
{
	this->QuickLoadFromFiles("mug");

	this->alcohol = new Alcohol(750, 7);
}


Mug::~Mug()
{
	delete this->modelMatrix;
}

void Mug::Draw()
{
	this->LoadDefaultPerspectiveMatrix();
	
	glm::mat4 *V = this->viewMatrix;
	glm::mat4 *M = new glm::mat4(1.0f);
	this->modelMatrix = M;

	*M = glm::translate(*M, glm::vec3(11.1f, 3.35f, -10.15f));
	*M = glm::scale(*M, glm::vec3(5, 5, 5));
	*M = glm::rotate(*M, 300.0f, glm::vec3(0, 1, 0));

	glLoadMatrixf(glm::value_ptr(*V**M));

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(253.0 / 255, 1, 202.0 / 255);
	if (this->collisionDetected)
		glColor3f(1.0f, 0.0f, 0.0f);
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void Mug::NextFrame()
{
	//
}
