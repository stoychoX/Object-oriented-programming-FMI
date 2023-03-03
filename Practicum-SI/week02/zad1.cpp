#include <iostream>
#include <fstream>

void writeSumAndProduct(const char* fileName, const int a, const int b, const int c) {
	std::ofstream output(fileName);
	if (!output.is_open()) {
		return;
	}

	output << (a + b + c) << std::endl << (a * b * c) << std::endl;
	output.close();
}

void printDifferenceFromFile(const char* fileName) {
	std::ifstream input(fileName);
	if (!input.is_open()) {
		return;
	}

	int firstNumber, secondNumber;
	input >> firstNumber;
	input.ignore();
	input >> secondNumber;
	input.close();

	std::cout << (firstNumber - secondNumber) << std::endl;
}

int main()
{
	int a, b, c;
	std::cin >> a >> b >> c;
	writeSumAndProduct("result.txt", a, b, c);
	printDifferenceFromFile("result.txt");
}