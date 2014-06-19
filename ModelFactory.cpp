#include "ModelFactory.h"

ModelFactory::ModelFactory(void)
{
}


ModelFactory::~ModelFactory(void)
{
}

void ModelFactory::CreateObjectsToDraw(std::map<std::string,Model*> *objects)
{
		(*objects)["room"] =  new RoomModel();

		(*objects)["glass"] = new Glass();

		(*objects)["beerBottle"] = new BeerBottle();

		(*objects)["barrel"] = new Barrel();

		(*objects)["mug"] = new Mug();

		(*objects)["shelves"] = new Shelves();

		(*objects)["lamp"] = new Lamp();

		(*objects)["beerCan"] = new BeerCan();
}

CollisionStatus* ModelFactory::GetNoCollisionStatus()
{
	auto status = new CollisionStatus();
	*status = CollisionStatus::none;
	return status;
}

void ModelFactory::GetObjectsForCollisionsCheck(std::map<std::string,Model*> *objects, std::map<Model*,CollisionStatus*> *collidableObjects)
{
		Model* object;
		CollisionStatus *status;
		
		object = (*objects)["beerBottle"];
		status = GetNoCollisionStatus();
		(*collidableObjects)[object]=status;

		object = (*objects)["mug"];
		status = GetNoCollisionStatus(); //tak, za kazdym razem tworzy nowy status, kazdy obiekt ma swoj unikalny
		(*collidableObjects)[object]=status;

		object = (*objects)["beerCan"];
		status = GetNoCollisionStatus();
		(*collidableObjects)[object]=status;
		

		
}
