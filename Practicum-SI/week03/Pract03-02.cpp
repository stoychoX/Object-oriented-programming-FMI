#include <iostream>
#include <fstream>

struct Example {
	int data = -1;
	char buff[8] = "err";
};

void saveToStruct(Example* myExArr, size_t size)
{
	int data = 0;
	char buff[8] = "Invalid";
	for (int i = 0; i < size; i++)
	{
		std::cin >> data;
		std::cin.ignore();
		std::cin.getline(buff, 8);
		myExArr[i].data = data;
		strcpy_s(myExArr[i].buff, buff);
	}
}

void saveStructToFile(const char* filePath, const Example* myExArr, size_t size)
{
	std::ofstream myInputFile(filePath, std::ios::binary | std::ios::app | std::ios::out);
	myInputFile.write((const char*)myExArr, sizeof(Example) * size);
	myInputFile.close();
	delete[] myExArr;
}

size_t getFileSize(std::ifstream& ifs)
{
	int currPointerPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t fileSize = ifs.tellg();
	ifs.seekg(currPointerPos);
	return fileSize;
}

size_t examplesInFile(const char* filePath)
{
	std::ifstream myFile(filePath, std::ios::binary | std::ios::app);
	if (!myFile.is_open())
	{
		return 0;
	}
	size_t fileSize = getFileSize(myFile);
	size_t howManyStructsInFile = fileSize / sizeof(Example);
	return howManyStructsInFile;
}

bool isThereStructWithPatternValue(const char* filePath, const char* pattern)
{
	std::ifstream myFile(filePath);
	if (!myFile.is_open())
	{
		return false;
	}
	size_t howManyStructs = examplesInFile(filePath);
	Example* structArray = new Example[howManyStructs];
	for (int i = 0; i < howManyStructs; i++)
	{
		myFile.read((char*)&structArray[i], sizeof(Example));
	}
	bool isPrinted = false;
	for (int i = 0; i < howManyStructs; i++)
	{
		if (strcmp(structArray[i].buff, pattern) == 0)
		{
			std::cout << structArray[i].data << " " << structArray[i].buff;
			isPrinted = true;
			break;
		}
	}
	if (!isPrinted)
	{
		Example newEx;
		std::cout << newEx.data << " " << newEx.buff;
	}
	return true;
}

int main()
{
	int n = 0;
	std::cin >> n;
	Example* myExArr = new Example[n];
	saveToStruct(myExArr, n);
	saveStructToFile("test.txt", myExArr, n);
	//std::cout << examplesInFile("test.txt");
	isThereStructWithPatternValue("test.txt", "werwer");
}