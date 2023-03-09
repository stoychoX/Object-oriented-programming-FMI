#pragma once
#include <iostream>
const short MAX_NAME_LEN = 25;

union IP {
	uint32_t address;
	unsigned char octets[4];
};

struct Time {
	short hours;
	short minutes;
	short seconds;
};

struct Log {
	char name[MAX_NAME_LEN];
	IP ip;
	Time time;
};

void WriteTimeInFile(const Time& time, std::ofstream& outFile)
{
	outFile << time.hours << ' ' << time.minutes << ' ' << time.seconds << ';';
}

void WriteLog(const Log& toWrite, std::ofstream& outFile)
{
	outFile << toWrite.name << ';' << toWrite.ip.address << ';';
	WriteTimeInFile(toWrite.time, outFile);
	outFile << "\n";
}

void WriteLogs(Log* logs, size_t size, const char* filePath)
{
	std::ofstream fileOut(filePath);
	if (!fileOut.is_open()) return;

	for (size_t i = 0; i < size; i++)
	{
		WriteLog(logs[i], fileOut);
	}

	fileOut.close();
}

void CreateLog(Log& toCreate)
{
	std::cin >> toCreate.name;
	std::cin >> toCreate.ip.address;
	std::cin >> toCreate.time.hours;
	std::cin >> toCreate.time.minutes;
	std::cin >> toCreate.time.seconds;
}

void CreateLogs(Log* toCreate, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << i << " log: ";
		CreateLog(toCreate[i]);
		std::cout << std::endl;
	}
}

uint32_t ParseIpFromCharToUnint32(char ipBuffer[])
{
	uint32_t ip = 0;
	int index = 0;
	while (ipBuffer[index] != '\0')
	{
		ip *= 10;
		ip += (ipBuffer[index] - 48);
		index++;
	}

	return ip;
}

void ReadLog(Log& toRead, std::ifstream& inFile)
{
	inFile.getline(toRead.name, MAX_NAME_LEN, ';');
	char ipBuffer[10];
	inFile.getline(ipBuffer, 10, ';');
	toRead.ip.address = ParseIpFromCharToUnint32(ipBuffer);
	inFile >> toRead.time.hours;
	inFile >> toRead.time.minutes;
	inFile >> toRead.time.seconds;
	inFile.ignore();
}

void PrintLog(const Log& log)
{
	std::cout << log.name << ' ' << log.ip.address << ' ';
	std::cout << log.time.hours << ':' << log.time.minutes << ':'
		<< log.time.seconds << std::endl;
}

size_t LogsCountInFile(std::ifstream& inFile)
{
	short countLogs = 0;
	while (true)
	{
		char buffer[1024] = "";
		inFile.getline(buffer, 1024);
		if (inFile.eof())
		{
			break;
		}
		countLogs++;
	}

	return countLogs;
}

size_t ReadLogs(Log* logs, const char* filePath)
{
	std::ifstream fileIn(filePath);
	if (!fileIn.is_open()) return -1;

	size_t size = LogsCountInFile(fileIn);
	fileIn.clear();
	fileIn.seekg(0, std::ios::beg);

	for (size_t i = 0; i < size; i++)
	{
		ReadLog(logs[i], fileIn);
	}
	fileIn.close();

	return size;
}

void ExecuteTask4()
{
	/*std::ofstream fileOut("logs.txt");
	if (!fileOut.is_open()) return;

	Log log;
	CreateLog(log);
	WriteLog(log, fileOut);*/

	const int size = 3;
	Log logs[size];
	CreateLogs(logs, size);
	WriteLogs(logs, size, "logs.txt");
	
	//std::ifstream fileOut("logs.txt");
	//if (!fileOut.is_open()) return;
	//Log log;
	//ReadLog(log, fileOut);
	//PrintLog(log);
	/*std::cout << LogsCountInFile(fileOut);*/
	//fileOut.close();
}