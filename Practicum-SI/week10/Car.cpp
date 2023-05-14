#include "Car.h"
#include "insufficient_fuel_error.h"

Car::Car(const FuelTank& tank, const Engine& engine, const Tire tires[4], const Battery& battery,
	double weight) :_tank(tank), _engine(engine), _battery(battery), _mileage(0), _weight(weight)
{
	for (size_t i = 0; i < 4; i++)
	{
		_tires[i] = tires[i];
	}
}
const FuelTank& Car::getFuelTank() const
{
	return _tank;
}
void Car::drive(double km)
{
	/*if (km > 0)
	{
		if (km <= _tank.getLitresLeft())
		{
			_tank.setLitresLeft(_tank.getLitresLeft() - km);
			_mileage += km;
		}
	}*/
	try
	{
		_tank.use(km);
	}
	catch (const insufficient_fuel_error& ex)
	{
		std::cout << ex.what();
		throw;
	}
	catch (...)
	{
		std::cout << "Unknown error!\n";
		throw;
	}
	_mileage += km;
	
}
Result dragRace(Car& car1, Car& car2)
{
	static const double dragMileage = 0.4;
	bool isCar1Finished = true;
	bool isCar2Finished = true;
	try
	{
		car1.drive(dragMileage);
	}
	catch (const insufficient_fuel_error& ex)
	{
		isCar1Finished = false;
		std::cout << "The first car was not able to finish the race!\n";
	}
	catch (...)
	{
		std::cout << "Unknown error!\n";
		throw;
	}

	try
	{
		car2.drive(dragMileage);
	}
	catch (const insufficient_fuel_error& ex)
	{
		isCar2Finished = false;
		std::cout << "The second car was not able to finish the race!\n";
	}
	catch (...)
	{
		std::cout << "Unknown error!\n";
		throw;
	}
	//here we use & instead of &&, bcs we should compare both values
	//(elselike if car1 is finished => !isCar1Finished is false, so the car2 check is not made)
	if (!isCar1Finished & !isCar2Finished)
	{
		return Result::Draw;
	}
	if (isCar1Finished & isCar2Finished)
	{
		static const double epsilon = 0.0000001;
		double car1Coef = car1._weight / car1._engine.getHP();
		double car2Coef = car2._weight / car2._engine.getHP();

		return abs(car1Coef - car2Coef) < epsilon ? Result::Draw :
			car1Coef > car2Coef ? Result::First : Result::Second;
	}
	return isCar1Finished ? Result::First : Result::Second;
}
std::ostream& operator<<(std::ostream& os, Result res)
{
	switch (res)
	{
	case Result::First:
		std::cout << "The first car wins!\n";
		break;
	case Result::Second:
		std::cout << "The second car wins!\n";
		break;
	case Result::Draw:
		std::cout << "It is a draw!\n";
		break;
	default:
		break;
	}
	return os;
}