#include "Table.h"


Table::Table()
{
	this->QuickLoadFromFiles("table");
	this->flattenData();
}


Table::~Table()
{
}

void Table::Draw()
{
	this->LoadDefaultPerspectiveMatrix();
	
	glm::mat4 *V = this->viewMatrix;
	glm::mat4 M = glm::mat4(1.0f);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(134.0 / 255, 86.0 / 255, 30.0 / 255);
	
	
	M = glm::scale(M, glm::vec3(4.0f, 5.0f, 5.0f));
	M = glm::translate(M, glm::vec3(1.8f, 0.6f, -0.66f));
	M = glm::rotate(M, 90.0f, glm::vec3(0, 1.0f, 0));

	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();



	glDisable(GL_COLOR_MATERIAL);
}

void Table::NextFrame()
{
	//
}
