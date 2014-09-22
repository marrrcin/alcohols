#include "Alcohol.h"


Alcohol::Alcohol(int volume = 0, int power = 0)
{
	this->volume = volume;
	this->power = power;
	this->volumeConst = volume;
}


Alcohol::~Alcohol()
{
}

void Alcohol::reset()
{
	this->volume = this->volumeConst;
}