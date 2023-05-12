#include "Car.h"

Car::Car(double fuelTankCap, 
	unsigned horsePwr, const char* engineManName, const char* engineDesc,
	unsigned width, unsigned prof, unsigned diam, const char* tireManName, const char* tireDesc,
	unsigned accCap, const char* accBatteryId, const char* accManName, const char* accDesc,
	unsigned carWeight) : tank(fuelTankCap), engine(engineManName, engineDesc, horsePwr), 
											acc(accManName, accDesc, accCap, accBatteryId)
{
	//tires!!
	if (carWeight <= 0)
		carWeight = 1000;
	weight = carWeight;
}