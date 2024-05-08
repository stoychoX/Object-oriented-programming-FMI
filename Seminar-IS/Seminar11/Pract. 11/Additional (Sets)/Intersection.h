#pragma once
#include "Set.h"

class Intersection : public Set
{
private:
	const Set* lhs;
	const Set* rhs;

public:
	Intersection(const Set* lhs, const Set* rhs);
	bool operator[](int element) const override;
	void print(std::ostream& stream) const override;
};

