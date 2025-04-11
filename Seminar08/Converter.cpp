#include "Converter.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstring>

const char* CURRENCY_RATES_FILE_PATH = "rates.txt";

double CurrencyConverter::convert(const char* from, const char* to, double amount) const
{
	if (!CurrencyRate::isValidRateString(from) || !CurrencyRate::isValidRateString(to))
		throw std::invalid_argument("Invalid currency passed");

	for (size_t i = 0; i < ratesCount; i++)
	{
		if (rates[i].shouldApplyRate(from, to))
		{
			rates[i].apply(amount);
			return amount;
		}
	}

	std::ostringstream oss;
	oss << "Currency conversion from " << from << " to " << to << " was not found.";

	throw std::runtime_error(oss.str());
}

CurrencyConverter& CurrencyConverter::getInstance()
{
	static CurrencyConverter instance;
	static bool initialized = false;

	if (initialized == false)
	{
		if(instance.loadFromFile(CURRENCY_RATES_FILE_PATH))
			initialized = true;
	}
	
	return instance;
}

static unsigned countSymbol(std::ifstream& inFile, char symbol)
{
	unsigned counter = 0;
	while (true)
	{
		if (inFile.get() == symbol)
			++counter;

		if (inFile.eof())
			break;
	}

	inFile.clear(); // Set the `good` state back.
	inFile.seekg(0, std::ios::beg);

	return counter;
}

static unsigned countLines(std::ifstream& inFile)
{
	return countSymbol(inFile, '\n') + 1;
}

bool CurrencyConverter::loadFromFile(const char* file)
{
	std::ifstream inFile(file);

	if (!inFile.is_open())
	{
		// Keep the last valid state.
		return false;
	}

	if (!inFile.good())
	{
		return false;
	}

	unsigned linesCount = countLines(inFile);
	CurrencyRate* candidateRates = new CurrencyRate[linesCount];

	for (unsigned index = 0; index < linesCount; index++)
	{
		bool isLastRecord = (index == linesCount - 1);
		// If any of them is not loaded
		// keep the old state of the object.
		if (!candidateRates[index].initialize(inFile, isLastRecord))
		{
			delete[] candidateRates;
			return false;
		}
	}

	clear();
	ratesCount = linesCount;
	rates = candidateRates;

	return true;
}

void CurrencyConverter::clear()
{
	delete[] rates;
	rates = nullptr;

	ratesCount = 0;
}

void CurrencyConverter::showRates() const
{
	for (size_t i = 0; i < ratesCount; i++)
	{
		rates[i].print();
		std::cout << std::endl;
	}
}

CurrencyConverter::~CurrencyConverter()
{
	clear();
}

bool CurrencyRate::isValidRateString(const char* str)
{
	return (str != nullptr) && (strlen(str) == CurrencyRate::RATE_SIZE);
}

bool CurrencyRate::shouldApplyRate(const char* from, const char* to) const
{
	return (strncmp(from, this->from, RATE_SIZE) == 0) &&
		(strncmp(to, this->to, RATE_SIZE) == 0);
}

bool CurrencyRate::initialize(std::ifstream& inFile, bool isLastRecord)
{
	inFile.getline(from, CurrencyRate::RATE_SIZE + 1, ' ');
	inFile.getline(to, CurrencyRate::RATE_SIZE + 1, ' ');
	inFile >> factor;

	if (isLastRecord && inFile.eof())
		return true;

	// skip the new line
	inFile.get();

	return inFile.good();
}

void CurrencyRate::apply(double& amount)
{
	amount *= factor;
}

void CurrencyRate::print() const
{
	std::cout << '[' << from << " -> " << to << ": " << factor << ']';
}
