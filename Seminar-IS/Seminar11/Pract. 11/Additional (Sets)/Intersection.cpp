#include "Intersection.h"

Intersection::Intersection(const Set* lhs, const Set* rhs)
	:lhs(lhs), rhs(rhs) {}

bool Intersection::operator[](int element) const
{
	return (*lhs)[element] && (*rhs)[element];

	// lhs->operator[](element) && rhs->operator[](element)
}

void Intersection::print(std::ostream& stream) const
{
	stream << "intersection: " << std::endl;

	lhs->print(stream);
	rhs->print(stream);
}
