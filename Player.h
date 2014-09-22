#pragma once
#include "Alcohol.h"
#include "stdafx.h"


class Player
{
public:
	Player();
	~Player();
	int intoxicationLevel; // 0-100;
	void drinkAlcohol(Alcohol *alcohol);
	void updateIntoxicationLevel(int alcoholVolume);
};

