#include "ModelFactory.h"

ModelFactory::ModelFactory(void)
{
}


ModelFactory::~ModelFactory(void)
{
}

void ModelFactory::CreateObjectsToDraw(std::map<std::string, Model*> *objects)
{
	std::cout << "\t\t> Creating: room..." << std::endl;
	(*objects)["room"] = new RoomModel();

	std::cout << "\t\t> Creating: glass..." << std::endl;
	(*objects)["glass"] = new Glass();

	std::cout << "\t\t> Creating: beer bottle..." << std::endl;
	(*objects)["beerBottle"] = new BeerBottle();

	std::cout << "\t\t> Creating: barrel..." << std::endl;
	(*objects)["barrel"] = new Barrel();

	std::cout << "\t\t> Creating: mug..." << std::endl;
	(*objects)["mug"] = new Mug();

	std::cout << "\t\t> Creating: shelves..." << std::endl;
	(*objects)["shelves"] = new Shelves();

	std::cout << "\t\t> Creating: lamp..." << std::endl;
	(*objects)["lamp"] = new Lamp();

	std::cout << "\t\t> Creating: beer can..." << std::endl;
	(*objects)["beerCan"] = new BeerCan();

	std::cout << "\t\t> Creating: wine bottle..." << std::endl;
	(*objects)["wineBottle"] = new WineBottle();

	std::cout << "\t\t> Creating: cognac..." << std::endl;
	(*objects)["cognac"] = new Cognac();

	std::cout << "\t\t> Creating: vodka..." << std::endl;
	(*objects)["vodka"] = new Vodka();

	std::cout << "\t\t> Creating: champagne..." << std::endl;
	(*objects)["champagne"] = new Champagne();

	std::cout << "\t\t> Creating: absinthe..." << std::endl;
	(*objects)["absinthe"] = new Absinthe();
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
		status = GetNoCollisionStatus(); 
		(*collidableObjects)[object]=status;

		object = (*objects)["beerCan"];
		status = GetNoCollisionStatus();
		(*collidableObjects)[object]=status;
		
		object = (*objects)["wineBottle"];
		status = GetNoCollisionStatus();
		(*collidableObjects)[object] = status;

		object = (*objects)["cognac"];
		status = GetNoCollisionStatus();
		(*collidableObjects)[object] = status;

		object = (*objects)["vodka"];
		status = GetNoCollisionStatus();
		(*collidableObjects)[object] = status;

		object = (*objects)["champagne"];
		status = GetNoCollisionStatus();
		(*collidableObjects)[object] = status;

		object = (*objects)["absinthe"];
		status = GetNoCollisionStatus();
		(*collidableObjects)[object] = status;

}
