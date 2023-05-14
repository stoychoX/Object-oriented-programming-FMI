#pragma once
#include "MyString.h"
#include <iostream>
class CarPart
{
private:
	size_t _id = 0;
	MyString _producerName;
	MyString _descrption;
protected:
	CarPart(size_t id, const MyString& producerName, const MyString& description);
public:
	size_t getId() const;
	const MyString& getProducerName()const;
	const MyString& getDescription()const;
	void setId(size_t id);
	void setProducerName(const MyString& prName);
	void setDescription(const MyString& descr);
};
std::ostream& operator<<(std::ostream& os, const CarPart& part);