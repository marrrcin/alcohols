#pragma once
#define MAX_LIGHT_COUNT 5
#include "stdafx.h"

typedef struct _light
{
	float position[4];
	float color[4];
	float radius;
	float intensity;

} Light;

class Lights
{
public:
	Lights();
	~Lights();
	void addLight(float x, float y, float z, float r, float g, float b, float radius, float intensity);

	int lightCount;
	std::vector<Light*> *lights;

};

