#pragma once
#include "Animal.h"

class AnimalFactory
{
public:
	static Animal* create(AnimalType type);
};

