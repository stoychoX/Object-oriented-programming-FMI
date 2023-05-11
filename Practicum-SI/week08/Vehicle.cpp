#include "Vehicle.h"
void Vehicle::copyFrom(const Vehicle& other)
{
	reg = new Registration(other.reg->toString());//???
	desc = new char[strlen(other.desc) + 1];
	strcpy(desc, other.desc);
}
void Vehicle::free()
{
	delete reg;
	delete desc;
}
Vehicle::Vehicle(const Vehicle& other)
{
	copyFrom(other);
}
Vehicle& Vehicle::operator=(const Vehicle& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Vehicle::~Vehicle()
{
	free();
}
Vehicle::Vehicle(const char* reg, const char* desc)
{
	try
	{
		this->reg = new Registration(reg);
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << "Vehicle cannot be created!";
		std::cout << ex.what() << std::endl;
	}
	if (desc == nullptr)
	{
		delete this->reg;//here that?
		this->reg = nullptr;
		throw std::invalid_argument("String does not exist!");
	}
	
	this->desc = new char[strlen(desc) + 1];
	strcpy(this->desc, desc);
}
const Registration* Vehicle::getReg() const
{
	return reg;
}