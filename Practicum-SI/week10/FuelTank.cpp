#include "FuelTank.h"
#include <stdexcept>

FuelTank::FuelTank(double cap)
{
	if (cap <= 0)
		cap = 10;//primerno
	capacity = full = cap;
}
void FuelTank::use(double toUse)
{
	if (toUse < 0)
		toUse = 0;
	if (toUse >= full)
		throw std::logic_error("insufficient_fuel_error");//custom exception???
	full -= toUse;
}
void FuelTank::fill(double toFill)
{
	if (toFill > capacity - full) {
		full = capacity;
		return;
	}
	if (toFill < 0)
		toFill = 0;
	full += toFill;
}