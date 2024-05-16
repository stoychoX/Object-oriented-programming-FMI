#include "Farm.h"
#include <stdexcept>
#include <utility>
#include "AnimalFactory.h"
#include "Animal.h"

void Farm::free()
{
	for (size_t i = 0; i < size; i++)
		delete data[i];
	delete[] data;
}

void Farm::copyFrom(const Farm& other)
{
	data = new Animal * [other.capacity] {};
	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i]->clone();
}

void Farm::move(Farm&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	
	other.data = nullptr;
	other.size = other.capacity = 0;
}

void Farm::resize()
{
	capacity *= 2;

	Animal** newData = new Animal * [capacity] {};
	for (size_t i = 0; i < size; i++)
		newData[i] = data[i];

	delete[] data;
	data = newData;
}

Farm::Farm() :
	data(nullptr),
	size(0),
	capacity(8)
{
	data = new Animal*[capacity]{};
}

Farm::Farm(const Farm& other)
{
	copyFrom(other);
}

Farm::Farm(Farm&& other) noexcept
{
	move(std::move(other));
}

Farm& Farm::operator=(const Farm& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Farm& Farm::operator=(Farm&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

void Farm::addAnimal(AnimalType type)
{
	if (size == capacity)
		resize();

	data[size++] = AnimalFactory::create(type);
}

void Farm::makeSound() const
{
	for (size_t i = 0; i < size; i++)
	{
		data[i]->makeNoise();
	}
}

AnimalType Farm::getType(size_t idx) const
{
	if (idx >= size)
		throw std::runtime_error("[Farm::getType] - invalid index.");

	return data[idx]->getType();
}

Farm::~Farm()
{
	free();
}
