#include "Lights.h"
#include "glm/glm.hpp"

Lights::Lights()
{
	this->lights = new std::vector < Light* > ;
	this->lightCount = 0;
}


Lights::~Lights()
{
	delete[] this->lights;
}

void Lights::addLight(float x, float y, float z, float r, float g, float b, float radius, float intensity)
{
	Light *newLight = new Light();

	newLight->position[0] = x;
	newLight->position[1] = y;
	newLight->position[2] = z;
	newLight->position[3] = 1.0f;

	newLight->color[0] = r;
	newLight->color[1] = g;
	newLight->color[2] = b;
	newLight->color[3] = 1.0f;

	newLight->radius = abs(radius);
	newLight->intensity = abs(intensity);

	this->lights->push_back(newLight);
	this->lightCount++;

}