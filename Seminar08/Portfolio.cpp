#include "Portfolio.h"
#include <stdexcept>
#include <iostream>
#include "Converter.h"
#include <cstring>

const float Portfolio::GROWTH_FACTOR = 2.0f;

// Keep the object valid.
Portfolio::Portfolio(const Portfolio& other) :
	size(other.getSize()),
	capacity(other.getCapacity()),
	records(nullptr)
{
	try
	{
		copyDynamic(other);
	}
	catch (const std::invalid_argument& e)
	{
		free();
		throw;
	}
	catch (const std::logic_error& e)
	{
		free();
		throw;
	}
	catch (...)
	{
		free();
		throw;
	}
}

Portfolio& Portfolio::operator=(const Portfolio& other)
{
	if (this != &other)
	{
		Portfolio copy(other);
		swap(copy);
	}

	return *this;
}

unsigned Portfolio::getSize() const
{
	return size;
}

unsigned Portfolio::getCapacity() const
{
	return capacity;
}

void Portfolio::print() const
{
	for (size_t i = 0; i < size; i++)
	{
		records[i].print();
		std::cout << " ";
	}
	std::cout << std::endl;
}

// Idea: If currency is already contained 
//		 dont add it second time.
void Portfolio::add(double amount, const char* currency)
{
	if (size == capacity)
		resize();

	records[size++] = CurrencyRecord(amount, currency);
}

double Portfolio::convert(const char* currency, bool showDebugInfo) const
{
	double amount = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(currency, records[i].getCurrencyStr()) == 0)
		{
			amount += records[i].getAmount();
			continue;
		}

		try
		{
			amount += CurrencyConverter::getInstance().convert(
				records[i].getCurrencyStr(), currency, records[i].getAmount()
			);
		}
		catch (const std::exception& e)
		{
			if (showDebugInfo)
			{
				std::cout << "[ERROR]: " << e.what() << std::endl;
			}
		}
	}

	return amount;
}

void Portfolio::resize()
{
	if (capacity == 0)
	{
		records = new CurrencyRecord[1];
		capacity = 1;
		return;
	}

	unsigned newCapacity = GROWTH_FACTOR * capacity;

	CurrencyRecord* newRecords = new CurrencyRecord[newCapacity];

	for (size_t i = 0; i < size; i++)
	{
		newRecords[i] = records[i];
	}

	delete[] records;
	records = newRecords;
	capacity = newCapacity;
}

// Moving the object
void Portfolio::swap(Portfolio& other) noexcept
{
	records = other.records;
	other.records = nullptr;

	size = other.getSize();
	capacity = other.getCapacity();

	other.size = other.capacity = 0;
}

Portfolio::~Portfolio()
{
	free();
}

void Portfolio::copyDynamic(const Portfolio& other)
{
	records = new CurrencyRecord[other.getCapacity()];

	if (other.getSize() > other.getCapacity())
		throw std::logic_error("Size is greater than capacity.");

	for (size_t i = 0; i < other.getSize(); i++)
	{
		records[i].setAmount(other.records[i].getAmount());
		records[i].setCurrency(other.records[i].getCurrencyStr());
	}
}

void Portfolio::free()
{
	delete[] records;
	records = nullptr;
	size = capacity = 0;
}
