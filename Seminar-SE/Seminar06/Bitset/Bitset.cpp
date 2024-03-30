#include "Bitset.h"
#include <cstring>
#include <iostream>

void Bitset::free()
{
	delete[] data;
}

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

Bitset Bitset::Union(const Bitset& other) const
{
	size_t maxBucketsUsed = std::max(bucketsCount, other.bucketsCount);
	size_t minBucketsUsed = std::min(bucketsCount, other.bucketsCount);

	const Bitset& bigger = (limit > other.limit) ? *this : other;

	Bitset toReturn(bigger.limit);

	for (size_t i = 0; i < minBucketsUsed; i++)
		toReturn.data[i] = (data[i] | other.data[i]);

	for (size_t i = minBucketsUsed; i < maxBucketsUsed; i++)
		toReturn.data[i] = bigger.data[i];

	return toReturn;
}

Bitset Bitset::Intersect(const Bitset& other) const
{
    size_t intersectLimit = (limit < other.limit) ? limit : other.limit;
    size_t intersectBuckets = (limit < other.limit) ? bucketsCount : other.bucketsCount;

    Bitset toReturn(intersectLimit);

    for (size_t i = 0; i < intersectBuckets; i++)
        toReturn.data[i] = (data[i] & other.data[i]);

    toReturn.limit = intersectLimit;
    toReturn.bucketsCount = intersectBuckets;

    return toReturn;    
}

Bitset::~Bitset()
{
	free();
}
