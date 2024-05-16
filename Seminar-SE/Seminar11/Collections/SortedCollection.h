#pragma once
#include "DynamicCollection.h"

class SortedCollection : public DynamicCollection
{
	int lowerBound(int x) const;
	int upperBound(int x) const;
public:
	void add(int) override;
	void remove(int) override;
	size_t count(int) const override;
	bool contains(int) const override;
};