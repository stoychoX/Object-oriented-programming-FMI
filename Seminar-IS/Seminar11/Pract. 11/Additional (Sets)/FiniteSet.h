#pragma once
#include "Set.h"
#include <vector>

class FiniteSet : public Set
{
private:
	std::vector<int> setNumbers;

public:
	FiniteSet(const std::vector<int>& setNumbers);
	bool operator[](int element) const override;
	void print(std::ostream& stream) const override;
};

