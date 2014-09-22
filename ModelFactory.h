#pragma once
#include <map>
#include <string>
#include "Model.h"
#include "Drawer.h"
#include "Example1.h"
#include "RoomModel.h"
#include "Glass.h"
#include "BeerBottle.h"
#include "Closet.h"
#include "Table.h"
#include "Barrel.h"
#include "Mug.h"
#include "Shelves.h"
#include "Lamp.h"
#include "BeerCan.h"
#include "WineBottle.h"
#include "CollisionDetector.h"
#include "Cognac.h"
#include "Vodka.h"
#include "Champagne.h"

class ModelFactory
{
private:
	std::map<std::string, Model*> objectsToDraw;

	CollisionStatus* GetNoCollisionStatus();

public:
	ModelFactory(void);
	~ModelFactory(void);

	void CreateObjectsToDraw(std::map<std::string,Model*> *objects);
	void GetObjectsForCollisionsCheck(std::map<std::string,Model*> *objects, std::map<Model*,CollisionStatus*> *collidableObjects);
};

