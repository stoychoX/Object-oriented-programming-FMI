#pragma once
#include "Set.h"

class IntervalSet : public Set
{
private:
	int leftBound;
	int rightBound;

public:
	IntervalSet(int left, int right);
	bool operator[](int element) const override;
	void print(std::ostream& stream) const override;
};

