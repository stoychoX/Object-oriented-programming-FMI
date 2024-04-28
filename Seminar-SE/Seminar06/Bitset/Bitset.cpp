#include "Bitset.h"
#include <cstring>
#include <iostream>

void Bitset::free()
{
	delete[] data;
}

Bitset::Bitset() : Bitset(8) {}

void Bitset::copyFrom(const Bitset& other)
{
	data = new char[other.bucketsCount];
	limit = other.limit;
	bucketsCount = other.bucketsCount;

    for (size_t i = 0; i < bucketsCount; i++)
        data[i] = other.data[i];
}

size_t Bitset::bucketsNeeded(size_t n) const
{
	size_t toReturn = n / 8;

	if (n % 8 != 0)
		++toReturn;
	
	return toReturn;
}

size_t Bitset::getBucket(size_t n) const
{
	return n / 8;
}

size_t Bitset::getPosition(size_t n) const
{
	return n % 8;
}

Bitset::Bitset(size_t n)
{
	bucketsCount = bucketsNeeded(n);
	data = new char[bucketsCount] {};
	limit = n;
}

void Bitset::addNumber(size_t number)
{
	if (number >= limit)
		return;
	size_t bucket = getBucket(number);
	size_t position = getPosition(number);

	data[bucket] |= (1ull << position);
}

void Bitset::removeNumber(size_t number) const
{
	if (number >= limit)
		return;
	size_t bucket = getBucket(number);
	size_t position = getPosition(number);

	data[bucket] &= ~(1ull << position);
}

bool Bitset::hasNumber(size_t number) const
{
	if (number >= limit)
		return false;
	size_t bucket = getBucket(number);
	size_t position = getPosition(number);

	return ((data[bucket] & (1ull << position)) != 0);
}

void Bitset::print() const
{
	for (size_t i = 0; i < limit; i++)
	{
		if (hasNumber(i))
		{
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}

Bitset::Bitset(const Bitset& other)
{
	copyFrom(other);
}

Bitset& Bitset::operator=(const Bitset& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Bitset Union(const Bitset& lhs, const Bitset& rhs)
{
	size_t maxBucketsUsed = std::max(lhs.bucketsCount, rhs.bucketsCount);
	size_t minBucketsUsed = std::min(lhs.bucketsCount, rhs.bucketsCount);

	const Bitset& bigger = (lhs.limit > rhs.limit) ? lhs : rhs;

	Bitset toReturn(bigger.limit);

	for (size_t i = 0; i < minBucketsUsed; i++)
		toReturn.data[i] = (lhs.data[i] | rhs.data[i]);

	for (size_t i = minBucketsUsed; i < maxBucketsUsed; i++)
		toReturn.data[i] = bigger.data[i];

	return toReturn;
}

Bitset Intersect(const Bitset& lhs, const Bitset& rhs)
{
    size_t intersectLimit = (lhs.limit < rhs.limit) ? lhs.limit : rhs.limit;
    size_t intersectBuckets = (lhs.limit < rhs.limit) ? lhs.bucketsCount : rhs.bucketsCount;

    Bitset toReturn(intersectLimit);

    for (size_t i = 0; i < intersectBuckets; i++)
        toReturn.data[i] = (lhs.data[i] & rhs.data[i]);

    toReturn.limit = intersectLimit;
    toReturn.bucketsCount = intersectBuckets;

    return toReturn;    
}

Bitset::~Bitset()
{
	free();
}
