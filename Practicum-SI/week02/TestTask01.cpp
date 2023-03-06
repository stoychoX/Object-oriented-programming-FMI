#include <iostream>
#include <fstream>
int main() {
	int first, second, third;
	std::cin >> first >> second >> third;
	std::ofstream writeInFile("result.txt", std::ios::trunc);
	if (!writeInFile.is_open()) {
		std::cout << "Error" << std::endl;
		return -1;
	}
	int sum = first + second + third;
	int multplc = first * second * third;
	writeInFile << "Sum: " << sum << std::endl;
	writeInFile << "Multplc: " << multplc << std::endl;
	writeInFile.close();
}