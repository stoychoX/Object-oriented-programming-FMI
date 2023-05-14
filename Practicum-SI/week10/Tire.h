#pragma once
#include "CarPart.h"

class Tire :public CarPart
{
private:
	double _width = 0;
	double _profile = 0;
	double _diameter = 0;
public:
	Tire();
	Tire(size_t id, const MyString& producerName, const MyString& description,
		double width, double profile, double diameter);

	double getWidth()const;
	double getProfile()const;
	double getDiameter()const;
	void setWidth(double width);
	void setProfile(double profile);
	void setDiameter(double diameter);
};
std::ostream& operator<<(std::ostream& os, const Tire& part);