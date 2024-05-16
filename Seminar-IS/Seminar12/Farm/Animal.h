#pragma once

enum class AnimalType
{
	Cat,
	Dog, Cow
};

class Animal
{
public:
	virtual void makeNoise() const = 0;
	virtual ~Animal() = default;
	virtual AnimalType getType() const = 0;

	virtual Animal* clone() const = 0;
};

