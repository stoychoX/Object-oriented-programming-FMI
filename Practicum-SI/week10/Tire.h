#pragma once
#include "CarPart.h"
#include <iostream>

class Tire : public CarPart
{
	unsigned widthMM;
	unsigned prof;
	unsigned diamInch;
public:
	Tire() = default;
	Tire(const char* _prodName, const char* _desc, unsigned _width, unsigned _prof, unsigned _diam);
	void setWidth(unsigned _width);
	void setProf(unsigned _prof);
	void setDiam(unsigned _diam);

	unsigned getWidht() const;
	unsigned getProf() const;
	unsigned getDiam() const;
	friend std::ostream& operator<<(std::ostream& os, Tire& acc);
};