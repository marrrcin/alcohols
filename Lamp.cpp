#include "Lamp.h"


Lamp::Lamp(void)
{
	this->QuickLoadFromFiles("lamp");
	this->lastTime = 0;
	this->speed = 110;
	this->currentAngle = 0;
	this->flattenData();
}


Lamp::~Lamp(void)
{
}

void Lamp::Draw()
{
	this->LoadDefaultPerspectiveMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);

	glm::mat4 M = glm::mat4(1.0f);
	M = glm::scale(M,glm::vec3(0.8f,0.8f,0.8f));
	M = glm::translate(M,glm::vec3(7.3f,12.05f,-6.2f));
	M = glm::rotate(M,this->currentAngle,glm::vec3(0,1,0));
	glm::mat4 *V = this->viewMatrix;
	


	glLoadMatrixf(glm::value_ptr(*V*M));
	this->RenderObject();
	glDisable(GL_COLOR_MATERIAL);
}

void Lamp::NextFrame()
{
	int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-lastTime;
	lastTime=actTime;
	this->currentAngle+=this->speed*interval/1000.0;
	if (this->currentAngle>360) this->currentAngle-=360;
}
