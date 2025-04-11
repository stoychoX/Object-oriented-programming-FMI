#include "Portfolio.h"
#include "Converter.h"
#include <iostream>

int main() 
{
	CurrencyConverter::getInstance().showRates();

	Portfolio p;

	p.add(10, "USD");
	p.add(20, "BGN");
	p.add(30, "EUR");

	std::cout << p.convert("BGN", true);
}