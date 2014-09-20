#include "Lights.h"
#include "glm/glm.hpp"

Lights::Lights()
{
	this->lightCount = 0;
}


Lights::~Lights()
{
}

void Lights::addLight(float x, float y, float z, float r, float g, float b, float radius, float intensity)
{

	this->positions[4 * lightCount + 0] = x;
	this->positions[4 * lightCount + 1] = y;
	this->positions[4 * lightCount + 2] = z;
	this->positions[4 * lightCount + 3] = 1.0f;

	this->colors[4 * lightCount + 0] = r;
	this->colors[4 * lightCount + 1] = g;
	this->colors[4 * lightCount + 2] = b;
	this->colors[4 * lightCount + 3] = 1.0f;

	this->radius[lightCount] = abs(radius);
	this->intensity[lightCount] = abs(intensity);

	this->lightCount++;

}