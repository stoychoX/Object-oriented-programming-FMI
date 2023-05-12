#pragma once
#include "FuelTank.h"
#include "Accumulator.h"
#include "Engine.h"
#include "Tire.h"

class Car
{
	FuelTank tank;
	Engine engine;
	Tire tires[4];
	Accumulator acc;
	unsigned km = 0;
	unsigned weight;//kg
public:
	Car() = default;
	Car(double fuelTankCap,
		unsigned horsepwr, const char* engineManName, const char* engineDesc,
		unsigned width, unsigned prof, unsigned diam, const char* tireManName, const char* tireDesc,
		unsigned accCap, const char* accBatteryId, const char* accManName, const char* accDesc,
		unsigned carWeight);
};