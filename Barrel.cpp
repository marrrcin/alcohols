#include "Barrel.h"


Barrel::Barrel()
{
	this->QuickLoadFromFiles("barrel");
}


Barrel::~Barrel()
{
}

void Barrel::Draw()
{
	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 M2;

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(130.0 / 255,104.0 / 255, 77.0 / 255);

	//ta w lewym narozniku (patrzac od duzych okien)
	M = glm::scale(M, glm::vec3(0.97f, 0.97f, 0.97f));
	M = glm::translate(M, glm::vec3(0, 1.9f, 0));
	M = glm::translate(M, glm::vec3(14.0f, 0, -10.0f));
	M2 = M;
	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();

	//dalsza
	M = glm::translate(M, glm::vec3(0, 0, 2.7f));
	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();

	//ta po prawej od naroznika
	M2 = glm::translate(M2, glm::vec3(-2.5f, 0, -0.5f));
	glLoadMatrixf(glm::value_ptr(*V*M2));
	this->RenderObject();

	//gorna
	M = glm::translate(M, glm::vec3(0, 2.5f, -1.25f));
	M = glm::rotate(M, 90.0f, glm::vec3(1, 0, 0));
	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();



	glDisable(GL_COLOR_MATERIAL);
}

void Barrel::NextFrame()
{
	//

}