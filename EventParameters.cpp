#include "EventParameters.h"

EventParameters::EventParameters(void)
{
	this->perspectiveAngle=50.0f;
	this->cameraRotation=0.0f;

	this->center=glm::vec3(0.0f,0.0f,0.0f);
	this->observer=glm::vec3(0.0f,3.5f,-35.0f);
	this->nose=glm::vec3(0.0f, 1.0f, 0.0f);

	this->light3on=true;
}


EventParameters::~EventParameters(void)
{
}
