#pragma once
#include "Set.h"

class Union : public Set
{
private:
	const Set* lhs;
	const Set* rhs;

public:
	Union(const Set* lhs, const Set* rhs);
	bool operator[](int element) const override;
	void print(std::ostream& stream) const override;
};

