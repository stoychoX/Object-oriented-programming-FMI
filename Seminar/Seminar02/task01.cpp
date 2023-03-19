#include<iostream>
#include<fstream>

size_t getFileSize(const char* filePath) {
	std::ifstream inFile(filePath);

	if (!inFile.is_open())
		return 0;

	inFile.seekg(0, std::ios::end);
	size_t size = (size_t)inFile.tellg();

	inFile.close();
	return size;
}

int main() {
    std::cout << getFileSize("task01.cpp");
}