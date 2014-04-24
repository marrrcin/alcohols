#pragma once
#include "Model.h"
class Drawer
{
protected:
	virtual void PassMatrixesToAllObjects(glm::mat4 *viewMatrix, glm::mat4 *pMatrix);
public:
	Drawer();
	~Drawer();

	void Display();
	void PrepareNextFrame();

	void CreateObjectsToDraw();

	std::map<std::string, Model*> objectsToDraw;
};

