#include "Cow.h"
#include <iostream>

void Cow::makeNoise() const
{
	std::cout << "Moo.." << std::endl;
}

AnimalType Cow::getType() const
{
	return AnimalType::Cow;
}

Animal* Cow::clone() const
{
	return new Cow(*this);
}
