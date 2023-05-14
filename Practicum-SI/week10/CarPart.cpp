#include "CarPart.h"
#include <iostream>

CarPart::CarPart(size_t id, const MyString& producerName, const MyString& description)
{
	if (id == 0)
	{
		throw std::invalid_argument("Id was 0!");
	}
	setId(id);
	setProducerName(producerName);
	setDescription(description);
}
size_t CarPart::getId() const
{
	return _id;
}
const MyString& CarPart::getProducerName()const
{
	return _producerName;
}
const MyString& CarPart::getDescription()const
{
	return _descrption;
}
void CarPart::setId(size_t id)
{
	if (id != 0)
	{
		_id = id;
	}
}
void CarPart::setProducerName(const MyString& prName)
{
	_producerName = prName;
}
void CarPart::setDescription(const MyString& descr)
{
	_descrption = descr;
}
std::ostream& operator<<(std::ostream& os, const CarPart& part)
{
	os << "(" << part.getId() << ") by " << part.getProducerName() << " - " << part.getDescription();
	return os;
}