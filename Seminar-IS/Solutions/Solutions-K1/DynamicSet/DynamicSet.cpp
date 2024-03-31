#include "DynamicSet.h"
#include <cstring>
#pragma warning (disable:4996)


DynamicSet::DynamicSet() : DynamicSet("EmptySet", 0, 255, nullptr, 0) {}

DynamicSet::DynamicSet(
	const char* name,
	unsigned a, unsigned b,
	unsigned* numbers, size_t size) : start(a), end(b)
{
	setName(name);

	unsigned numbersCount = b - a + 1;

	bucketsCount = numbersCount / Constants::elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount]{};

	for (size_t i = 0; i < size; i++)
	{
		if (!contains(numbers[i]))
		{
			invert(numbers[i]);
		}
	}
}

void DynamicSet::free()
{
	delete[] buckets;//!!!
	bucketsCount = 0;
	buckets = nullptr;
}
void DynamicSet::copyFrom(const DynamicSet& other)
{
	buckets = new uint8_t[other.bucketsCount];
	bucketsCount = other.bucketsCount;

    for (size_t i = 0; i < bucketsCount; i++)
        buckets[i] = other.buckets[i];    

	start = other.start;
	end = other.end;
	setName(other.name);
}

const char* DynamicSet::getName() const
{
	return name;
}

void DynamicSet::setName(const char* name)
{
	if (name == nullptr || strlen(name) > 31)
		return;

	strcpy(this->name, name);
}

DynamicSet::DynamicSet(const DynamicSet& other)
{
	copyFrom(other);
}

DynamicSet& DynamicSet::operator=(const DynamicSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
DynamicSet::~DynamicSet()
{
	free();
}

unsigned DynamicSet::getBucketIndex(unsigned num) const
{
	return num / Constants::elementsInBucket;
}

bool DynamicSet::inInterval(unsigned number) const
{
	return (number >= start && number <= end);
}

void DynamicSet::invert(unsigned num)
{
	if (!inInterval(num))
		return;

	num -= start;

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % Constants::elementsInBucket;

	buckets[bucketIndex] ^= (1 << bitIndex);
}

unsigned DynamicSet::elementsCount() const
{
	unsigned count = 0;
	for (size_t i = start; i < end; i++)
	{
		if (contains(i))
			++count;
	}
	return count;
}

void DynamicSet::clear()
{
	for (size_t i = 0; i < bucketsCount; i++)
		buckets[i] = 0;
}

bool DynamicSet::subset(const DynamicSet& other) const
{
	unsigned from = std::min(start, other.start);
	unsigned to = std::max(end, other.end);

	for (size_t i = from; i <= to; i++)
	{
		if (contains(i) && !other.contains(i))
			return false;
	}
	return true;
}

bool DynamicSet::contains(unsigned num) const
{
	if (!inInterval(num))
		return false;
	num -= start;

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % Constants::elementsInBucket;

	uint8_t mask = 1 << bitIndex;

	return buckets[bucketIndex] & mask;
}

DynamicSet DynamicSet::UnionOfSets(const DynamicSet& rhs) const
{
	if (start != rhs.start || end != rhs.end)
		return DynamicSet();

	DynamicSet result(*this);
	result.setName("Union");

	for (int i = 0; i < result.bucketsCount; i++)
		result.buckets[i] |= rhs.buckets[i];

	return result;
}

void DynamicSet::print() const
{
    for (size_t i = start; i <= end; i++)
    {
        if(contains(i))
            std::cout << i << " ";
    }
    std::cout << std::endl;
}

DynamicSet DynamicSet::IntersectionOfSets(const DynamicSet& rhs) const
{
	if (start != rhs.start || end != rhs.end)
		return DynamicSet();

	DynamicSet result(*this);
	result.setName("Intersection");

	for (int i = 0; i < result.bucketsCount; i++)
		result.buckets[i] &= rhs.buckets[i];

	return result;
}