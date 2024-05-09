#include "FiniteSet.h"

FiniteSet::FiniteSet(const Vector& inputNumbers)
	:setNumbers(inputNumbers) {}

bool FiniteSet::operator[](int element) const
{
	for (size_t i = 0; i < setNumbers.size(); i++)
	{
		if (setNumbers[i] == element)
		{
			return true;
		}
	}

	return false;
}

void FiniteSet::print(std::ostream& stream) const
{
	stream << "Finite: ";

	for (size_t i = 0; i < setNumbers.size(); i++)
	{
		stream << setNumbers[i] << " ";
	}

	stream << std::endl;
}
