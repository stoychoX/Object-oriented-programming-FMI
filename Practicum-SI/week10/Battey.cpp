#include "Battery.h"

Battery::Battery(size_t id, const MyString& producerName, const MyString& description,
	double capacity, const MyString& batteryId) :CarPart(id, producerName, description)
{
	if (capacity < 0)
	{
		throw std::invalid_argument("Capacity was negative!\n");
	}
	setCapacity(capacity);
	setId(batteryId);
}
double Battery::getCapacity()const
{
	return _capacity;
}
const MyString& Battery::getId()
{
	return _id;
}
void Battery::setCapacity(double capacity)
{
	if (capacity >= 0)
	{
		_capacity = capacity;
	}
}
void Battery::setId(const MyString& id)
{
	_id = id;
}
std::ostream& operator<<(std::ostream& os, const Battery& part)
{
	os << (CarPart)part << part.getCapacity() << " Ah";
	return os;
}