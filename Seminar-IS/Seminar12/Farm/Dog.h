#pragma once
#include "Animal.h"
class Dog :
    public Animal
{
public:
	void makeNoise() const override;
	AnimalType getType() const override;
	Animal* clone() const override;
};

