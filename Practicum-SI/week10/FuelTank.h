#pragma once

class FuelTank
{
	double capacity = 0;
	double full = 0;
public:
	FuelTank() = default;
	FuelTank(double cap);
	void use(double toUse);
	void fill(double toFill);
};