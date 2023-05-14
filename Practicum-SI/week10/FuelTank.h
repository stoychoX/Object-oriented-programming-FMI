#pragma once
class FuelTank
{
private:
	double _capacity = 0;
	double _litresLeft = 0;
public:
	FuelTank(double capacity);
	double getCapacity()const;
	double getLitresLeft()const;
	void setCapacity(double capacity);
	void setLitresLeft(double litresLeft);

	void use(double toUse);
	void fill(double toFill);
};