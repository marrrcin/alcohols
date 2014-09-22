#pragma once
#include "Model.h"
#include "EventParameters.h"
#include "CollisionDetector.h"
#include "Player.h"

class Drawer
{
protected:
	virtual void PassMatrixesToAllObjects(glm::mat4 *viewMatrix, glm::mat4 *pMatrix);
public:
	Drawer(EventParameters *params);
	~Drawer();

	void Display();
	void PrepareNextFrame();

	void CreateObjectsToDraw();
	void AssignModelMover();
	void HandleCollisions();


	std::map<std::string, Model*> objectsToDraw;
	std::map<Model*, CollisionStatus*> collidableObjects;

	EventParameters *params;
	Player *player;
};

