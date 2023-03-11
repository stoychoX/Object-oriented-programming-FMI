#include<iostream>
#include<fstream>

#pragma warning (disable : 4996)

struct Student {
	char* name;
	int age;
};

Student createStudent(const char* argName, int argAge) {
	Student toReturn;

	size_t nameLen = strlen(argName);

	toReturn.name = new char[nameLen + 1];
	strcpy(toReturn.name, argName);

	toReturn.age = argAge;

	return toReturn;
}

void writeStudent(std::ofstream& outFile, const Student& arg) {
	size_t nameLen = strlen(arg.name);

	outFile.write((const char*)&nameLen, sizeof(nameLen));
	outFile.write(arg.name, nameLen + 1);
	outFile.write((const char*)&arg.age, sizeof(arg.age));
}

Student readStudent(std::ifstream& inFile) {
	Student toReturn;
	size_t nameLen = 0;

	inFile.read((char*)&nameLen, sizeof(nameLen));
	toReturn.name = new char[nameLen + 1];

	inFile.read(toReturn.name, nameLen + 1);
	inFile.read((char*)&toReturn.age, sizeof(toReturn.age));

	return toReturn;
}

void freeStudent(Student& arg) {
	delete[] arg.name;
	arg.name = nullptr;
}

int main() {
	Student example[2]; 
	example[0] = createStudent("Nikola Svetoslavov", 23);
	example[1] = createStudent("Ivan Angelov", 19);
	std::ofstream outFile("file.txt", std::ios::binary | std::ios::trunc);
	for (size_t i = 0; i < 2; i++)
		writeStudent(outFile, example[i]);

	outFile.close();

	std::ifstream inFile("file.txt", std::ios::binary);
	for (size_t i = 0; i < 2; i++) {
		Student nikolaCopy = readStudent(inFile);
		std::cout << nikolaCopy.name << " " << nikolaCopy.age << std::endl;
	}	
	
	inFile.close();
	for (size_t i = 0; i < 2; i++)
		freeStudent(example[i]);
}