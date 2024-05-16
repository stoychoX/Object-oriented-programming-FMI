#pragma once
#include "Animal.h"
class Cat : public Animal
{
public:
	void makeNoise() const override;
	AnimalType getType() const override;

	Animal* clone() const override;
};

