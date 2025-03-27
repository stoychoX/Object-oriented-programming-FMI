#include "prize.h"
#include "utils.h"
#include <fstream>
#include <cstring>
#include <iostream>

#pragma warning (disable : 4996)

ReadStatus readPrizes(const char* filePath, Price*& prizes, unsigned& size)
{
	std::ifstream inFile(filePath, std::ios::binary);

	if (!inFile.is_open())
	{
		return ReadStatus::FileNotFound;
	}

	unsigned fileSize = getFileSize(inFile);
	size = fileSize / sizeof(Price);

	prizes = new Price[size];
	inFile.read((char*)(prizes), size * sizeof(Price));

	return ReadStatus::OK;
}

WriteStatus writePrices(const char* filePath, const Price* prizes, unsigned size)
{
	if (prizes == nullptr)
	{
		return WriteStatus::Nullptr;
	}

	std::ofstream outFile(filePath, std::ios::binary);

	if (!outFile.is_open())
	{
		return WriteStatus::FileNotFound;
	}

	outFile.write((const char*)(prizes), size * sizeof(Price));

	return WriteStatus::OK;
}

void printPrize(const Price& prize)
{
	std::cout << prize.amount << " " << prize.currency << std::endl;
}

Price createPrice(double amount, const char* currency)
{
	Price toReturn;
	toReturn.amount = amount;

	strncpy(toReturn.currency, currency, 3);
	toReturn.currency[3] = '\0';
	return toReturn;
}