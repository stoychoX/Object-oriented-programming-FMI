#pragma once
#include <iostream>

class insufficient_fuel_error :std::logic_error
{
	char* _message = nullptr;
public:
	insufficient_fuel_error(const char* message);
	const char* what()const;
};