#pragma once
#include "CarPart.h"

class Engine : public CarPart
{
	unsigned horsePwr = 0;
public:
	Engine() = default;
	Engine(const char* _prodName, const char* _desc, unsigned _horsePwr);

	void setHorsePwr(unsigned _horsePwr);
	unsigned getHorsePwr() const;
};