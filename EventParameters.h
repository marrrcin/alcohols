#pragma once
#include "stdafx.h"
#include "ModelMover.h"

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
	bool crouch;
	bool collisionAction;

	ModelMover *modelMover;
	Action currentAction;
	ActionAxis actionAxis;
	float ax, ay, az;
};

