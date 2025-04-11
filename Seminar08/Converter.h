#pragma once
#include <fstream>

class CurrencyRate
{
public:
	static const short RATE_SIZE = 3;
	static bool isValidRateString(const char* str);

	bool shouldApplyRate(const char* from, const char* to) const;
	bool initialize(std::ifstream& inFile, bool isLastRecord);
	void apply(double& amount);
	void print() const;

private:
	char from[RATE_SIZE + 1] = {};
	char to[RATE_SIZE + 1] = {};
	double factor = 0.0;
};

class CurrencyConverter
{
public:
	CurrencyConverter(const CurrencyConverter&) = delete;
	CurrencyConverter& operator=(const CurrencyConverter&) = delete;

	double convert(const char* from, const char* to, double amount) const;

	static CurrencyConverter& getInstance();

	bool loadFromFile(const char* file);
	void clear();
	void showRates() const;

	~CurrencyConverter();
private:
	CurrencyConverter() = default;

	CurrencyRate* rates = nullptr;
	unsigned ratesCount = 0;
};