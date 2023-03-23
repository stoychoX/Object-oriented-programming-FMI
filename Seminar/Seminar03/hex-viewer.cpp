#include<iostream>
#include<fstream>

struct HexViewer {
	unsigned char* data;
	size_t size;
};

size_t getFileSize(std::ifstream& inFile) {
	size_t cPos = inFile.tellg();

	inFile.seekg(0, std::ios::end);
	size_t size = (size_t)inFile.tellg();

	inFile.seekg(cPos);
	return size;
}

HexViewer load(const char* filePath) {
	std::ifstream inFile(filePath, std::ios::binary);
	HexViewer toReturn;

	toReturn.size = getFileSize(inFile);
	toReturn.data = new unsigned char[toReturn.size];
	inFile.read((char*)toReturn.data, toReturn.size);
	return toReturn;
}

void freeHex(HexViewer& arg) {
	delete[] arg.data;
}

void view(const HexViewer& arg) {
	for (size_t i = 0; i < arg.size; i++)
		std::cout << std::hex << (unsigned int)arg.data[i] << " ";
	std::cout << std::endl;

	for (size_t i = 0; i < arg.size; i++) {
		if (std::islower(arg.data[i]) || std::isupper(arg.data[i]))
			std::cout << arg.data[i] << " ";
		else
			std::cout << ".. ";
	}
}

void change(HexViewer& arg, size_t at, char c) {
	if (at > arg.size)
		return;
	arg.data[at] = c;
}

void remove(HexViewer&, size_t);
void save(const char*, const HexViewer&);

int main() {
	HexViewer example = load("file.txt");
	view(example);
	freeHex(example);
}