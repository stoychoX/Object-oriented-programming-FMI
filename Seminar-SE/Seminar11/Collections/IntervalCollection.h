#pragma once
#include "DynamicCollection.h"
class IntervalCollection : public DynamicCollection
{
	unsigned _a = 0;
	unsigned _b = 0;

	bool inInterval(int) const;
public:
	IntervalCollection(unsigned a, unsigned b);
	virtual void add(int) override;
	virtual void remove(int) override;
	virtual size_t count(int) const override;
	virtual bool contains(int) const override;
};

