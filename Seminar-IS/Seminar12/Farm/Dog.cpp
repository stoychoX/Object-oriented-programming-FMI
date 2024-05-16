#include "Dog.h"
#include<iostream>

void Dog::makeNoise() const
{
	std::cout << "Bark..." << std::endl;
}

AnimalType Dog::getType() const
{
	return AnimalType::Dog;
}

Animal* Dog::clone() const
{
	return new Dog(*this);
}
