#include "CarPart.h"
#include <iostream>
#include <stdexcept>

unsigned CarPart::carPartsCreated = 0;

void CarPart::free()
{
	delete[] prodName;
	delete[] desc;
	prodName = desc = nullptr;
	id = 0;
}
void CarPart::moveFrom(CarPart&& other)
{
	prodName = other.prodName;
	other.prodName = nullptr;
	desc = other.desc;
	other.desc = nullptr;
	id = other.id;
}
CarPart::CarPart(const char* _prodName, const char* _desc)
{
	setProdName(_prodName);
	try {
		setDesc(_desc);
	}
	catch (std::invalid_argument) {
		free();
	}
	id = ++carPartsCreated;
}
CarPart::CarPart(CarPart&& other)
{
	moveFrom(std::move(other));
}
CarPart& CarPart::operator=(CarPart&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
CarPart::~CarPart()
{
	free();
}
void CarPart::setProdName(const char* _prodName)
{
	if (_prodName == nullptr)
		throw std::invalid_argument("string doesn't exist");
	prodName = new char[strlen(_prodName) + 1];
	strcpy(prodName, _prodName);
}
void CarPart::setDesc(const char* _desc)
{
	if (_desc == nullptr)
		throw std::invalid_argument("string doesn't exist");
	desc = new char[strlen(_desc) + 1];
	strcpy(desc, _desc);
}
const char* CarPart::getProdName() const
{
	return prodName;
}
const char* CarPart::getDesc() const
{
	return desc;
}
unsigned CarPart::getId() const
{
	return id;
}