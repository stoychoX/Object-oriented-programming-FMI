#include "Tire.h"

Tire::Tire(const char* _prodName, const char* _desc, unsigned _width, unsigned _prof, unsigned _diam) : CarPart(_prodName, _desc)
{
	setWidth(_width);
	setProf(_prof);
	setDiam(_diam);
}

void Tire::setWidth(unsigned _width)
{
	if (_width < 155 || _width > 365)
	{
		_width = 155;
	}
	widthMM = _width;
}
void Tire::setProf(unsigned _prof)
{
	if (_prof < 30 || _prof > 80)
	{
		_prof = 30;
	}
	prof = _prof;
}
void Tire::setDiam(unsigned _diam)
{
	if (_diam < 13 || _diam > 21)
	{
		_diam = 13;
	}
	diamInch = _diam;
}
unsigned Tire::getWidht() const
{
	return widthMM;
}
unsigned Tire::getProf() const
{
	return prof;
}
unsigned Tire::getDiam() const
{
	return diamInch;
}