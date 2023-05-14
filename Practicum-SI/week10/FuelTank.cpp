#include "FuelTank.h"
#include <iostream>
#include "insufficient_fuel_error.h"

FuelTank::FuelTank(double capacity)
{
	if (capacity < 0)
	{
		throw std::invalid_argument("Capacity was negative!\n");
	}
	setCapacity(capacity);
	setLitresLeft(capacity);
}
double FuelTank::getCapacity()const
{
	return _capacity;
}
double FuelTank::getLitresLeft()const
{
	return _litresLeft;
}
void FuelTank::setCapacity(double capacity)
{
	if (capacity >= 0)
	{
		_capacity = capacity;
		if (_litresLeft > capacity)
		{
			_litresLeft = capacity;
		}
	}
	else
	{
		_capacity = 0;
	}
}
void FuelTank::setLitresLeft(double litresLeft)
{
	if (litresLeft >= 0)
	{
		if (_capacity < litresLeft)
		{
			_litresLeft = _capacity;
		}
		else
		{
			_litresLeft = litresLeft;
		}
	}
	else
	{
		_litresLeft = 0;
	}
}

void FuelTank::use(double toUse)
{
	if (toUse > 0)
	{
		if (toUse > getLitresLeft())
		{
			throw insufficient_fuel_error("Litres is tank less than the desired usage!\n");
		}
		setLitresLeft(getLitresLeft() - toUse);
	}
}
void FuelTank::fill(double toFill)
{
	if (toFill > 0)
	{
		setLitresLeft(getLitresLeft() + toFill);
	}
}