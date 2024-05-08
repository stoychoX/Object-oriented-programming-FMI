#pragma once
#include "Criteria.h"
#include "Set.h"
class CriteriaSet : public Set
{
private:
	Criteria criteria;
	std::vector<int> setNumbers;

public:
	CriteriaSet(const std::vector<int>& setNumbers, Criteria criteria);
	bool operator[](int element) const override;
	void print(std::ostream& stream) const override;
};

