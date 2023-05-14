#pragma once
#include "CarPart.h"

class Battery :public CarPart
{
private:
	double _capacity = 0;
	MyString _id;
public:
	Battery(size_t id, const MyString& producerName, const MyString& description,
		double capacity, const MyString& batteryId);
	double getCapacity()const;
	const MyString& getId();
	void setCapacity(double capacity);
	void setId(const MyString& id);
};
std::ostream& operator<<(std::ostream& os, const Battery& part);