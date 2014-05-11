#include "Closet.h"


Closet::Closet()
{
	this->QuickLoadFromFiles("closet1");
}


Closet::~Closet()
{
}

void Closet::Draw()
{
	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 *V = this->viewMatrix;

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(134.0/255, 86.0/255, 30.0/255); //ugly brown

	//szafka nr 1
	M = glm::scale(M, glm::vec3(1.2f, 1.2f, 1.2f));
	M = glm::rotate(M, 90.0f,glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(-7.7f, 0.4f, 2.0f));
	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();

	//szafka nr 2
	M = glm::translate(M, glm::vec3(0.0f, 0, 5.0f));
	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();

	
	glDisable(GL_COLOR_MATERIAL);
}

void Closet::NextFrame()
{

	//
}
