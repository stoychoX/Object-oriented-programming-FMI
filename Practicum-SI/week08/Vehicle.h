#pragma once
#include "Registration.h"
class Vehicle
{
	Registration* reg = nullptr;
	char* desc = nullptr;
	void copyFrom(const Vehicle& other);
	void free();
public:
	Vehicle(const Vehicle& other);
	Vehicle& operator=(const Vehicle& other);
	~Vehicle();
	Vehicle(const char* reg, const char* desc);
	const Registration* getReg() const;
};