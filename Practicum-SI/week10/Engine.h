#pragma once
#include "CarPart.h"
#include <iostream>

class Engine : public CarPart
{
	unsigned horsePwr = 0;
public:
	Engine() = default;
	Engine(const char* _prodName, const char* _desc, unsigned _horsePwr);

	void setHorsePwr(unsigned _horsePwr);
	unsigned getHorsePwr() const;
	friend std::ostream& operator<<(std::ostream& os, Engine& acc);
};