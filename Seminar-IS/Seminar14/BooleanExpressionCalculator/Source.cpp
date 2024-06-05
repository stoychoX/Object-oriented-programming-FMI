#include <iostream>
#include "ExpressionCalculator.h"

int main()
{
	ExpressionCalculator e("p | !p");

	std::cout << e.isTautology().value() << std::endl; // This is tautology
	std::cout << e.isContradiction().value() << std::endl; // But not contradiction

	e.tryParse("p & !p");

	std::cout << e.isTautology().value() << std::endl; // This is not tautology
	std::cout << e.isContradiction().value() << std::endl; // But contradiction

	// "if at least one of A or B is true, and each implies C, then C must be true as well"
	e.tryParse("((a | b) & (a > c) & (b > c)) > c");

	std::cout << e.isTautology().value() << std::endl;

	e.tryParse("(a | b) > (b | a)");
	
	std::cout << e.isTautology().value() << std::endl;
}