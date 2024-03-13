/* Task 1 */

#include <iostream>
#include <fstream>

void readFromFile()
{
	std::ifstream inFile("file.txt");
	if (!inFile.is_open())
		return;
	int sum = 0;
	int product = 0;

	inFile >> sum >> product;

	inFile.close();

	std::cout << sum - product;
}

void writeToFile(int a, int b, int c)
{
	std::ofstream outFile("file.txt");

	if (!outFile.is_open())
		return;

	int sum = a + b + c;
	int product = a * b * c;

	outFile << sum << " " << product;

	outFile.close();
}

int main()
{
	writeToFile(4, 5, 6);
	readFromFile();
}