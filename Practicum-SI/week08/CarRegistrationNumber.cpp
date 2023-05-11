#include <iostream>
#include "VehicleList.h"

int main()
{
	VehicleList vehicles(6);
	VehicleList vehicles2(5);
	try
	{
		vehicles.insert("BA1234BG", "b");
		vehicles.insert("AN1234BG", "c");
		vehicles.insert("BB1234BG", "b");
		vehicles.insert("AA1234BG", "b");
		vehicles.insert("AB1234BG", "b");
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
	catch (...)
	{
		std::cout << "Unknown error!";
	}
	const Vehicle* a = vehicles.find("AA1234BG");
	try
	{
		for (size_t i = 0; i < vehicles.size(); i++)
		{
			std::cout << vehicles.at(i).getReg()->toString() << std::endl;
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}

