#include <iostream>
#include <fstream>

struct Example {
	int data;
	char buff[8];
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

void saveStructToFile(const char* filePath,const Example* myExArr, size_t size)
{
	std::ofstream myInputFile(filePath, std::ios::binary | std::ios::app | std::ios::out);
	myInputFile.write((const char*)myExArr, sizeof(Example) * size);
	myInputFile.close();
}

int main()
{
	int n = 0;
	std::cin >> n;
	Example* myExArr = new Example[n];
	saveToStruct(myExArr, n);
	saveStructToFile("test.txt", myExArr, n);
	delete[] myExArr;
}
