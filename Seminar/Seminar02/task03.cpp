#include<iostream>
#include<fstream>

#define BUFF_MAX_SIZE 1024

bool findPattern(char buff[BUFF_MAX_SIZE], const char* pattern, size_t len) {
	if (BUFF_MAX_SIZE < len)
		return false;

	for (size_t i = 0; i < len; i++)
		if (buff[i] != pattern[i])
			return false;

	return true;
}

size_t findBlockSize(std::ifstream& inFile) {
	size_t currentPos = inFile.tellg();
	char buff[BUFF_MAX_SIZE];
	size_t lines = 0;

	while (true) {
		inFile.getline(buff, BUFF_MAX_SIZE, '\n');

		if (inFile.eof())
			break;

		if (findPattern(buff, "#!sort", 6))
			break;

		++lines;
	}

	inFile.clear();
	inFile.seekg(currentPos);
	return lines;
}

void sort(char** lines, size_t length) {
	for (size_t i = 0; i < length - 1; i++) {
		size_t minElementIndex = i;

		for (size_t j = i + 1; j < length; j++) {
			if (strcmp(lines[minElementIndex], lines[j]) == 1)
				minElementIndex = j;
		}

		if (i != minElementIndex)
			std::swap(lines[minElementIndex], lines[i]);
	}
}

void sortSingleBlock(std::ifstream& inFile, std::ofstream& outFile) {
	size_t blockSize = findBlockSize(inFile);

	char** lines = new char* [blockSize];

	for (size_t i = 0; i < blockSize; i++)
		lines[i] = new char[BUFF_MAX_SIZE];

	for (size_t i = 0; i < blockSize; i++)
		inFile.getline(lines[i], BUFF_MAX_SIZE, '\n');

	sort(lines, blockSize);

	for (size_t i = 0; i < blockSize; i++)
		outFile << lines[i] << std::endl;

	for (size_t i = 0; i < blockSize; i++)
		delete[] lines[i];

	delete[] lines;
}

bool sortBlocks(const char* from, const char* to) {
	std::ifstream toSort(from);

	if (!toSort.is_open())
		return false;

	std::ofstream outFile(to);

	if (!outFile.is_open())
		return false;

	char buff[BUFF_MAX_SIZE];

	while (true) {
		toSort.getline(buff, BUFF_MAX_SIZE, '\n');

		if (toSort.eof())
			break;

		if (!findPattern(buff, "#sort", 5)) {
			outFile << buff << std::endl;
		}
		else {
			sortSingleBlock(toSort, outFile);
			toSort.ignore(BUFF_MAX_SIZE, '\n'); // #!sort
		}
	}

	outFile.close();
	toSort.close();
	return true;
}

int main() {
    
}