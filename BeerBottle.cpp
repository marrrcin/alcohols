#include "BeerBottle.h"

BeerBottle::BeerBottle()
{

	this->QuickLoadFromFiles("beer");
	glm::mat4 *M = new glm::mat4(1.0f);
	*M = glm::scale(*M,glm::vec3(0.2f,0.2f,0.2f));
	*M = glm::translate(*M,glm::vec3(-8.35f,8.4f,-2.5f));
	*M = glm::translate(*M,glm::vec3(-7.75f,13.25f,-2.8f));

	this->modelMatrix = M;
	

	this->lastTime=0;
	this->rotationAngle=0;
	this->rotationSpeed=140;
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

	if(*(this->collisionStatus)==CollisionStatus::handling)
	{
		if(!this->isHandling)
		{
			this->isHandling = true;
			this->rotationAngle=0.0;
			this->lastTime=glutGet(GLUT_ELAPSED_TIME);
			this->startTime=glutGet(GLUT_ELAPSED_TIME);
		}

		glm::mat4 M = *(this->modelMatrix);
		int actTime=glutGet(GLUT_ELAPSED_TIME);
		int interval=actTime-lastTime;
		lastTime=actTime;
		this->rotationAngle+=this->rotationSpeed*interval/1000.0;
		if (actTime-this->startTime>3000)
		{
			*(this->collisionStatus)=CollisionStatus::handled;
			this->isHandling=false;
		}	

		M = glm::rotate(M,this->rotationAngle,glm::vec3(1,0,0));
		glLoadMatrixf(glm::value_ptr(*V*M));
	}
	else
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
