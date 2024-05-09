#pragma once
#include "Criteria.h"
#include "Set.h"
class CriteriaSet : public Set
{
private:
	Criteria criteria;
	Vector setNumbers;

public:
	CriteriaSet(const Vector& setNumbers, Criteria criteria);
	bool operator[](int element) const override;
	void print(std::ostream& stream) const override;
};

