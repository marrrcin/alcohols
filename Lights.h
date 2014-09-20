#pragma once
#define MAX_LIGHT_COUNT 5
#include "stdafx.h"


class Lights
{
public:
	Lights();
	~Lights();
	void addLight(float x, float y, float z, float r, float g, float b, float radius, float intensity);

	int lightCount;
	float positions[4 * MAX_LIGHT_COUNT];
	float colors[4 * MAX_LIGHT_COUNT];
	float radius[MAX_LIGHT_COUNT];
	float intensity[MAX_LIGHT_COUNT];

	int getLightCount()
	{
		return lightCount;
	}
};

