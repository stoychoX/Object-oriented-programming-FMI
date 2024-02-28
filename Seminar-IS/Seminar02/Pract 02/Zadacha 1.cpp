/* Task 1 */

#include <iostream>
#include <fstream>

void read()
{
	std::ifstream inFile("zapis.txt");
	if (!inFile.is_open())
		std::cout << "The file cannot be opened";
	int sum = 0;
	int product = 0;

	inFile >> sum >> product;

	inFile.close();

	std::cout << sum - product;
}

void zapis(int a, int b, int c)
{
	std::ofstream outFile("zapis.txt");

	if (!outFile.is_open())
		std::cout << "Can't open file";

	int sum = a + b + c;
	int product = a*b*c;
	
	outFile << sum << " " << product;

	outFile.close();
	read();
}

int main()
{
	zapis(4, 5, 6);
}