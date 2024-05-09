#pragma once
#include "Set.h"
#include "Vector.h"

class FiniteSet : public Set
{
private:
	Vector setNumbers;

public:
	FiniteSet(const Vector& setNumbers);
	bool operator[](int element) const override;
	void print(std::ostream& stream) const override;
};

