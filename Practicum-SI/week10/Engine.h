#pragma once
#include "CarPart.h"

class Engine :public CarPart
{
private:
	unsigned _horsePowers = 0;
public:
	Engine(size_t id, const MyString& producerName, const MyString& description, unsigned horsePowers);
	unsigned getHP()const;
	void setHP(unsigned hp);
};
std::ostream& operator<<(std::ostream& os, const Engine& part);