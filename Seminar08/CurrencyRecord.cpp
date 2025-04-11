#include "CurrencyRecord.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

#pragma warning (disable:4996)

Currency::Currency(const char* currency)
{
	setCurrency(currency);
}

void Currency::setCurrency(const char* currency)
{
	if (currency == nullptr)
		throw std::invalid_argument("Nullptr passed as argument for currency");

	unsigned size = strlen(currency);

	if (size < Currency::CURRENCY_LENGHT)
		throw std::invalid_argument("Currency too short");

	strncpy(this->currency, currency, Currency::CURRENCY_LENGHT);
	this->currency[Currency::CURRENCY_LENGHT] = '\0';
}

const char* Currency::getCurrency() const
{
	return currency;
}

CurrencyRecord::CurrencyRecord(double amount, const Currency& currency) :
	amount(amount),
	currency(currency)
{
}

CurrencyRecord::CurrencyRecord(double amount, const char* currency) :
	amount(amount),
	currency(currency)
{
}

void CurrencyRecord::setAmount(double amount)
{
	this->amount = amount;
}

void CurrencyRecord::setCurrency(const char* currency)
{
	this->currency.setCurrency(currency);
}

void CurrencyRecord::print() const
{
	std::cout << '[' << amount << " " << currency.getCurrency() << ']';
}

double CurrencyRecord::getAmount() const
{
	return amount;
}

const char* CurrencyRecord::getCurrencyStr() const
{
	return currency.getCurrency();
}
