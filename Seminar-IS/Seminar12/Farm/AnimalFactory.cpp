#include "AnimalFactory.h"
#include <stdexcept>

#include "Animal.h"
#include "Cat.h"
#include "Dog.h"
#include "Cow.h"

Animal* AnimalFactory::create(AnimalType type)
{
	Animal* toReturn = nullptr;
	switch (type)
	{
	case AnimalType::Cat:
		toReturn = new Cat;
		break;
	case AnimalType::Dog:
		toReturn = new Dog;
		break;
	case AnimalType::Cow:
		toReturn = new Cow;
		break;
	default:
		throw std::invalid_argument("[Farm::addAnimal] - invalid type");
		break;
	}
	return toReturn;
}
