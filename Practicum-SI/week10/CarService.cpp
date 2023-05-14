#include <iostream>
#include "Car.h"
#include "insufficient_fuel_error.h"

int main()
{
	FuelTank ft1(50);
	FuelTank ft2(70);

	Engine en1(12345, "Opel", "Very good!", 150);
	Engine en2(34256, "Ferrari", "Fast!", 200);

	Battery b1(32432, "Duracell", "Ok", 100, "a1234b");
	Battery b2(43243, "MaxMotion", "Good", 150, "b1334z");

	Tire tires1[4];
	for (size_t i = 0; i < 4; i++)
	{
		tires1[i] = { 14325, "Honda", "Summer", 100, 40, 20 };
	}
	Tire tires2[4];
	for (size_t i = 0; i < 4; i++)
	{
		tires2[i] = { 44443, "Taikan", "OffRoad", 150, 60, 25 };
	}


	Car car1(ft1, en1, tires1, b1, 1500);//coef 7
	Car car2(ft2, en2, tires2, b2, 2000);//coef 10,...

	try
	{
		car1.drive(49.8);
		car2.drive(70);
	}
	catch (const insufficient_fuel_error& ex)
	{
		std::cout << "Refill your car!" << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown error occured!\n";
		//what we should do in that case???
	}
	

	std::cout << dragRace(car1, car2);
}