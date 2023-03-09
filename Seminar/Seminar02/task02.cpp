#include<iostream>
#include<fstream>

size_t countOcuurences(std::ifstream& inFile, char c) {
	size_t currentPos = inFile.tellg();
	inFile.seekg(0, std::ios::beg);

	size_t result = 0;

	while (true) {
		char currChar = inFile.get();

		if (inFile.eof())
			break;

		if (currChar == c)
			++result;
	}

	inFile.clear();
	inFile.seekg(currentPos);
	return result;
}

size_t linesCount(const char* filePath) {
	std::ifstream inFile(filePath);

	if (!inFile.is_open())
		return 0;

	size_t res = countOcuurences(inFile, '\n') + 1;
	inFile.close();
	return res;
}

int main() {
    std::cout << linesCount("task02.cpp");
}