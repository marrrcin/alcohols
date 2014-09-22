#include "Player.h"


Player::Player()
{
	this->intoxicationLevel = 0;
	this->sobered = false;
}


Player::~Player()
{
}

void Player::drinkAlcohol(Alcohol *alcohol)
{
	int alcoholVolume = 0; // objêtoœæ ³yczka * procent alko w ³yczku; ³yczek to 100ml lub mniej

	//wypij resztke alko
	if (alcohol->volume < 100)
	{
		alcoholVolume = alcohol->volume * alcohol->power / 100;
		alcohol->volume = 0;
	}
	else
	{
		alcohol->volume -= 100;
		alcoholVolume = alcohol->power; // wypij 100ml * n % = wypij  n ml czystego alko
	}

	this->updateIntoxicationLevel(alcoholVolume);
}

void Player::updateIntoxicationLevel(int alcoholVomume)
{
	this->intoxicationLevel += alcoholVomume;
	if(alcoholVomume != 0)
		std::cout << "Alcohol level: " << this->intoxicationLevel << std::endl;
}

void Player::soberUp()
{
	this->intoxicationLevel = 0;
	this->sobered = true;
}