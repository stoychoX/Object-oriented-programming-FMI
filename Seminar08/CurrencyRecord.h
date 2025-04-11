#pragma once

class Currency
{
private:
	static const short CURRENCY_LENGHT = 3;

	char currency[CURRENCY_LENGHT + 1] = {};
public:
	Currency() = default;
	Currency(const char* currency);

	void setCurrency(const char* currency);

	const char* getCurrency() const;
};

class CurrencyRecord
{
public:
	CurrencyRecord() = default;
	CurrencyRecord(double amount, const Currency& currency);
	CurrencyRecord(double amount, const char* currency);

	void setAmount(double amount);
	void setCurrency(const char* currency);

	void print() const;

	double getAmount() const;
	const char* getCurrencyStr() const;

private:
	double amount = 0.0;
	Currency currency;
};