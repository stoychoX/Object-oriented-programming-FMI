#include<iostream>
#include<fstream>

struct Example {
	int x;
	char data[8];
};

// Важна част:
void writeToFile(const char* filePath, Example* arg, size_t length) {
	std::ofstream outFile(filePath, std::ios::trunc | std::ios::binary);

	if (!outFile.is_open() || arg == nullptr)
		return;

	outFile.write((const char*)arg, length * sizeof(Example));

	outFile.close();
}

void initExample(Example& arg) {
	std::cin >> arg.x;
	std::cin.ignore();
	std::cin.getline(arg.data, 8, '\n');
}

size_t getFileSize(std::ifstream& inFile) {
	size_t cPos = inFile.tellg();

	inFile.seekg(0, std::ios::end);
	size_t size = (size_t)inFile.tellg();

	inFile.seekg(cPos);
	return size;
}

// Важна част:
Example* readFromFile(const char* filePath, size_t& size) {
	std::ifstream inFile(filePath, std::ios::binary);

	if (!inFile.is_open())
		return nullptr;

	size = getFileSize(inFile) / sizeof(Example);

	Example* toReturn = new Example[size];

	inFile.read((char*)toReturn, size * sizeof(Example));

	return toReturn;
}

int main() {
	Example arr[5];

	for (size_t i = 0; i < 5; i++)
		initExample(arr[i]);

	writeToFile("file.txt", arr, 5);

	size_t length = 0;

	Example* result = readFromFile("file.txt", length);

	for (size_t i = 0; i < length; i++)
		std::cout << result[i].x << " " << result[i].data << std::endl;

	delete[] result;
}