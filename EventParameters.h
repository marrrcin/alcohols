#pragma once
#include "stdafx.h"
class EventParameters
{

public:
	EventParameters(void);
	~EventParameters(void);

	glm::vec3 observer;
	glm::vec3 center;
	glm::vec3 nose;

	float perspectiveAngle;
	float cameraRotation;

	bool light3on;
};

