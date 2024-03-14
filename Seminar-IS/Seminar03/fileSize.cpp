#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& inFile)
{
	size_t currentLocation = inFile.tellg();
	inFile.seekg(0, std::ios::end);
	size_t fileSize = inFile.tellg();
	inFile.seekg(currentLocation, std::ios::beg);

	return fileSize;
}

int main()
{
    std::ifstream inFile("fileSize.cpp", std::ios::binary);
    std::cout << getFileSize(inFile);
}