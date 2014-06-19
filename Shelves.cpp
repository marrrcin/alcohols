#include "Shelves.h"


Shelves::Shelves(void)
{
	this->LoadModelFromObjFile("shelves.obj");
}


Shelves::~Shelves(void)
{
}

void Shelves::Draw()
{
	this->LoadDefaultPerspectiveMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);

	glm::mat4 M = glm::mat4(1.0f);
	M = glm::scale(M,glm::vec3(3.0f));
	M = glm::rotate(M,90.0f,glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 *V = this->viewMatrix;
	


	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void Shelves::NextFrame()
{
	//
}
