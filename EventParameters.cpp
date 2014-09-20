#include "EventParameters.h"

EventParameters::EventParameters(void)
{
	this->perspectiveAngle=50.0f;
	this->cameraRotation=0.0f;

	this->center=glm::vec3(0.0f,0.0f,0.0f);
	this->observer=glm::vec3(9.0f,5.0f,-7.0f);
	this->nose=glm::vec3(0.0f, 1.0f, 0.0f);

	this->light3on=false;
	this->crouch = false;
	this->collisionAction = false;
	this->printInfo = false;

	this->currentAction = translate;
	
	this->actionAxis = x;
	this->ax = 0;
	this->ay = 0;
	this->az = 0;
}


EventParameters::~EventParameters(void)
{
}
