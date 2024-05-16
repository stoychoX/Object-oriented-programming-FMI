#include "Cat.h"
#include <iostream>

void Cat::makeNoise() const
{
    std::cout << "Meow..." << std::endl;
}

AnimalType Cat::getType() const
{
    return AnimalType::Cat;
}

Animal* Cat::clone() const
{
    return new Cat(*this);
}
