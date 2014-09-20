#include "BeerCan.h"


BeerCan::BeerCan(void)
{
	this->LoadModelFromObjFile("can.obj"); // magic, do not touch
	//quickload doesn't work and I don't know why
	this->ExportLoadedMatrixesToFile("can");

	this->alcohol = new Alcohol(500, 6);
}


BeerCan::~BeerCan(void)
{
	delete this->modelMatrix;
}


void BeerCan::Draw()
{
	this->LoadDefaultPerspectiveMatrix();

	glm::mat4 *V = this->viewMatrix;
	glm::mat4 *M = new glm::mat4(1.0f);
	this->modelMatrix = M;

	*M = glm::scale(*M, glm::vec3(0.3f, 0.3f, 0.3f));
	*M = glm::translate(*M, glm::vec3(4.35f, 20.0f, 10.25f));
	*M = glm::rotate(*M, 90.0f, glm::vec3(0, 1, 0));
	*M = glm::translate(*M, glm::vec3(2.15f, -2.85f, 0));

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(*V**M));
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0f, 1.0f, 1.0f);
	if (*(this->collisionStatus) == CollisionStatus::detected || *(this->collisionStatus) == CollisionStatus::handling)
		glColor3f(1.0f, 0.0f, 0.0f);
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void BeerCan::NextFrame()
{
	//

}