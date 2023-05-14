#include "Tire.h"

Tire::Tire() :CarPart(1, "", ""), _width(155), _profile(30), _diameter(13) {}
Tire::Tire(size_t id, const MyString& producerName, const MyString& description,
	double width, double profile, double diameter) :CarPart(id, producerName, description)
{
	setWidth(width);
	setProfile(profile);
	setDiameter(diameter);
}
double Tire::getWidth()const
{
	return _width;
}
double Tire::getProfile()const
{
	return _profile;
}
double Tire::getDiameter()const
{
	return _diameter;
}
void Tire::setWidth(double width)
{
	if (width < 155)
	{
		_width = 155;
	}
	else if (width > 365)
	{
		_width = 365;
	}
	else
	{
		_width = width;
	}
}
void Tire::setProfile(double profile)
{
	if (profile < 30)
	{
		_profile = 30;
	}
	else if (profile > 80)
	{
		_profile = 80;
	}
	else
	{
		_profile = profile;
	}
}
void Tire::setDiameter(double diameter)
{
	if (diameter < 13)
	{
		_diameter = 13;
	}
	else if (diameter > 21)
	{
		_diameter = 21;
	}
	else
	{
		_diameter = diameter;
	}
}
std::ostream& operator<<(std::ostream& os, const Tire part)
{
	os << (CarPart)part << " - " << part.getWidth() << "/" << part.getProfile() << "R" << part.getDiameter();
	return os;
}