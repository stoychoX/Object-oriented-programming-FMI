#pragma once
#include "FuelTank.h"
#include "Engine.h"
#include "Tire.h"
#include "Battery.h"
#include <iostream>

enum class Result
{
	First,
	Second,
	Draw
};

class Car
{
private:
	FuelTank _tank;
	Engine _engine;
	Tire _tires[4];
	Battery _battery;
	double _mileage = 0;
	double _weight = 0;
public:
	Car(const FuelTank& tank, const Engine& engine, const Tire tires[4], const Battery& battery, double weight);
	const FuelTank& getFuelTank() const;
	void drive(double km);

	friend Result dragRace(Car& car1, Car& car2);
	//friend std::ostream& operator<<(std::ostream& os, const Car& car);
};
Result dragRace(Car& car1, Car& car2);
std::ostream& operator<<(std::ostream& os, Result res);