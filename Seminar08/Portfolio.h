#pragma once
#include "CurrencyRecord.h"

class Portfolio
{
public:
	Portfolio() = default;

	Portfolio(const Portfolio&);
	Portfolio& operator=(const Portfolio&);
	
	unsigned getSize() const;
	unsigned getCapacity() const;

	void print() const;
	void add(double amount, const char* currency);
	double convert(const char* currency, bool showDebugInfo = false) const;

	void resize();

	void swap(Portfolio& other) noexcept;

	~Portfolio();
private:
	void copyDynamic(const Portfolio&);
	void free();

	CurrencyRecord* records = nullptr;
	unsigned size = 0;
	unsigned capacity = 0;

	static const float GROWTH_FACTOR;
};