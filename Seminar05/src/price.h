#pragma once

enum class WriteStatus
{
	OK,
	Nullptr,
	FileNotFound
};

enum class ReadStatus
{
	OK,
	FileNotFound
};

struct Price
{
	double amount;
	char currency[4];
};

ReadStatus readPrizes(const char* filePath, Price*& prizes, unsigned& size);
WriteStatus writePrices(const char* filePath, const Price* prizes, unsigned size);
void printPrize(const Price& prize);
Price createPrice(double amount, const char* currency);