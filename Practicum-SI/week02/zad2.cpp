#include <iostream>
#include <fstream>

int getSymbols(const char* fileName) {
	std::ifstream input(fileName);
	if (!input.is_open()) {
		return -1;
	}

	int count = 0;
	while (true) {
		char ch = input.get();
		if (input.eof()) {
			break;
		}
		if (ch != 'a' && ch != 'd') {
			count++;
		}
	}

	return count;
}

int main() {
	std::cout << getSymbols("zad2.txt"); // file needs to be created first
}