#include "IntervalSet.h"

IntervalSet::IntervalSet(int left, int right)
	:leftBound(std::min(left, right)),
	rightBound(std::max(left, right)) {}

bool IntervalSet::operator[](int element) const
{
	return element >= leftBound && element <= rightBound;
}

void IntervalSet::print(std::ostream& stream) const
{
	stream << "Interval: " << leftBound << " : " << rightBound << std::endl;
}
