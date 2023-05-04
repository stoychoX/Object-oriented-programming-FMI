#include "Accumulator.h"
#include <iostream>

void Accumulator::free()
{
	delete[] batteryId;
	batteryId = nullptr;
	cap = 0;
}
void Accumulator::moveFrom(Accumulator&& other)
{
	batteryId = other.batteryId;
	other.batteryId = nullptr;
	cap = other.cap;
}

Accumulator::Accumulator(const char* _prodName, const char* _desc, unsigned _cap, const char* _battId) : CarPart(_prodName, _desc)
{
	cap = _cap;
	setBatteryId(_battId);
}
Accumulator::Accumulator(Accumulator&& other)
{
	moveFrom(std::move(other));
}
Accumulator& Accumulator::operator=(Accumulator&& other)
{
	if (this != &other)
	{
		CarPart::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
Accumulator::~Accumulator()
{
	free();
}

void Accumulator::setBatteryId(const char* _battId)
{
	batteryId = new char[strlen(_battId) + 1];
	strcpy(batteryId, _battId);
}

unsigned Accumulator::getCap() const
{
	return cap;
}
const char* Accumulator::getBattId() const
{
	return batteryId;
}