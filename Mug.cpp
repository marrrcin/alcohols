#include "Mug.h"


Mug::Mug()
{
	this->QuickLoadFromFiles("mug");
	glm::mat4 *M = new glm::mat4(1.0f);
	*M = glm::translate(*M, glm::vec3(11.1f, 3.35f, -10.15f));
	*M = glm::scale(*M, glm::vec3(5, 5, 5));
	*M = glm::rotate(*M, 300.0f, glm::vec3(0, 1, 0));

	this->modelMatrix = M;
}


Mug::~Mug()
{
}

void Mug::Draw()
{
	this->LoadDefaultPerspectiveMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(253.0 / 255, 1, 202.0 / 255);
	glm::mat4 *V = this->viewMatrix;
	
	glLoadMatrixf(glm::value_ptr(*V**this->modelMatrix));
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void Mug::NextFrame()
{
	//
}
