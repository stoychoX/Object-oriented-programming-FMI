#include "CriteriaSet.h"

CriteriaSet::CriteriaSet(const Vector& setNumbers, Criteria criteria)
	:criteria(criteria), setNumbers(setNumbers) {}

bool CriteriaSet::operator[](int element) const
{
	return criteria(setNumbers, element);

	//return criteria.operator()(setNumbers, element);
}

void CriteriaSet::print(std::ostream& stream) const
{
	stream << "Criteria set: " << std::endl;

	for (size_t i = 0; i < setNumbers.size(); i++)
	{
		stream << setNumbers[i] << " ";
	}

	stream << std::endl;
}
