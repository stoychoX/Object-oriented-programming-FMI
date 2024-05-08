#include "Union.h"

Union::Union(const Set* lhs, const Set* rhs)
	:lhs(lhs), rhs(rhs) {}

bool Union::operator[](int element) const
{
	return (*lhs)[element] || (*rhs)[element];

	// lhs->operator[](element) || rhs->operator[](element)
}

void Union::print(std::ostream& stream) const
{
	stream << "union: " << std::endl;

	lhs->print(stream);
	rhs->print(stream);
}
