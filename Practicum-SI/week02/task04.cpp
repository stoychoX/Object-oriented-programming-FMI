#include <iostream>
#include <fstream>
#pragma warning(disable: 4996)

union IpAddressV4 {
	int32_t num = 0;
	char octets[4];
};

struct logTime
{
	short hour = 0;
	short minutes = 0;
	short seconds = 0;
};

struct login
{
	char name[20];
	IpAddressV4 IpAddress;
	logTime timeOfLog;
};

bool WriteLog(const login& toWrite, std::ofstream& outFile)
{
	if (!outFile.is_open())
	{
		return false;
	}
	outFile << toWrite.name << std::endl;
	outFile << toWrite.IpAddress.num << std::endl;
	outFile << toWrite.timeOfLog.hour << " " << toWrite.timeOfLog.minutes
		<< " " << toWrite.timeOfLog.seconds << std::endl;
	return true;
}

login* MergeLogs(login* A, size_t lenA, login* B, size_t lenB)
{
	login* allLogs = new login[lenA + lenB];
	for (size_t i = 0; i < lenA; i++)
	{
		allLogs[i] = A[i];
	}
	for (size_t i = lenA; i < lenA + lenB; i++)
	{
		allLogs[i] = B[i - lenA];
	}
	return allLogs;
}

size_t ReadLogs(login* logs, const char* filePath);
bool WriteLogs(login* newLogs, size_t size, const char* filePath)
{
	login* existingLogs = new login[0];
	int countExistingLogs = ReadLogs(existingLogs, filePath);

	std::ofstream ofs(filePath);
	if (!ofs.is_open())
	{
		delete[] existingLogs;
		return false;
	}

	login* allLogs = MergeLogs(newLogs, size, existingLogs, countExistingLogs);

	for (size_t i = 0; i < size+countExistingLogs; i++)
	{
		bool hasLoged = WriteLog(allLogs[i], ofs);
		if (!hasLoged)
		{
			return false;
		}
	}
	ofs.close();
	return true;
}

bool ReadLog(login& log, std::ifstream& inFile)
{
	if (!inFile.is_open())
	{
		return false;
	}
	inFile.getline(log.name, 20);
	inFile >> log.IpAddress.num;
	inFile.ignore();
	inFile >> log.timeOfLog.hour >> log.timeOfLog.minutes >> log.timeOfLog.seconds;
	inFile.ignore();
	return true;
}

size_t GetCharCount(char symbol, const char* filePath)
{
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
	{
		return false;
	}
	size_t encounters = 0;
	size_t currPosition = ifs.tellg();
	while (true)
	{
		if (ifs.eof())
		{
			break;
		}
		char currSymbol = ifs.get();
		if (currSymbol == symbol)
		{
			encounters++;
		}
	}
	ifs.seekg(currPosition);
	ifs.clear();
	ifs.close();
	return encounters + 1;
}

size_t logsCount(const char* filePath)
{
	return GetCharCount('\n', filePath) / 3;
}

size_t ReadLogs(login* logs, const char* filePath)
{
	size_t loginsCount = logsCount(filePath);
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
	{
		return 0;
	}
	for (size_t i = 0; i < loginsCount; i++)
	{
		ReadLog(logs[i], ifs);
	}
	ifs.clear();
	return loginsCount;
}

IpAddressV4 ReadIpFromConsole()
{
	IpAddressV4 ip;
	int currOctet;
	for (size_t i = 0; i < 4; i++)
	{
		std::cin >> currOctet;
		std::cin.ignore();
		ip.octets[i] = currOctet;
	}
	return ip;

}

logTime GetLogTimeFromConsole()
{
	logTime logTime;
	std::cin >> logTime.hour;
	std::cin.ignore();
	std::cin >> logTime.minutes;
	std::cin.ignore();
	std::cin >> logTime.seconds;
	std::cin.ignore();
	return logTime;
}

login ReadLogFromConsole()
{
	login log;
	std::cin.getline(log.name, 20);
	log.IpAddress = ReadIpFromConsole();
	log.timeOfLog = GetLogTimeFromConsole();
	return log;
}

void PrintIP(IpAddressV4 ip)
{
	std::cout << (int)ip.octets[0] << "." << (int)ip.octets[1] << "."
		<< (int)ip.octets[2] << "." << (int)ip.octets[3] << std::endl;
}

void PrintTimeOfLog(logTime time)
{
	std::cout << time.hour << ":" << time.minutes << ":" << time.seconds << std::endl;
}

void PrintLogs(const login* logs, size_t countLogs)
{
	for (size_t i = 0; i < countLogs; i++)
	{
		std::cout << i + 1 << ". " << logs[i].name << std::endl;
		PrintIP(logs[i].IpAddress);
		PrintTimeOfLog(logs[i].timeOfLog);
	}
}

int main()
{
	//from file

	/*login* logs = new login[0];
	size_t countLogs = ReadLogs(logs, "Logs.txt");
	PrintLogs(logs, countLogs);*/

//example login file
/*
Dankata
16777343
12 30 15
Gerganata
16777343
15 15 30
Ivan Pauna
36777343
20 22 01
*/

    //from console
	login log = ReadLogFromConsole();
	login* logsNew = new login[1]{log};
	WriteLogs(logsNew ,1, "Logs.txt");
	login* logs = new login[0];
	int countLogs = ReadLogs(logs, "Logs.txt");
	PrintLogs(logs, countLogs);

//example input console
/*
Stoian Azmanov
127.0.2.3
12 34 45
*/
}
