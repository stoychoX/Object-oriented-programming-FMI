#include "Product.h"
#include <iostream>
#include <stdexcept>
#pragma warning (disable : 4996)

unsigned int Product::nextId = 0;

void Product::free()
{
	delete[] name;
}
void Product::moveFrom(Product&& other)
{
	this->id = other.id;
	this->name = other.name;
	other.name = nullptr;
}
Product::Product(Product&& other)
{
	moveFrom(std::move(other));
}
Product& Product::operator=(Product&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
Product::Product(const char* str)
{
	setName(str);
}
Product::~Product()
{
	free();
}
void Product::setName(const char* str)
{
	if (str == nullptr)
		throw std::invalid_argument("given string doesn't exist");

	this->name = new char[strlen(str) + 1];
	strcpy(name, str);
	this->id = nextId + 1;
	nextId++;
}
const char* Product::getName() const
{
	return this->name;
}
unsigned int Product::getId() const
{
	return this->id;
}