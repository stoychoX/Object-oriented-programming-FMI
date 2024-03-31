#pragma once
#include <iostream>
#include <cstddef>

namespace Constants 
{
	constexpr unsigned elementsInBucket = sizeof(uint8_t) * 8;
}

class DynamicSet
{
	char name[32]{};
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;

	unsigned start;
	unsigned end;

	void free();
	void copyFrom(const DynamicSet& other);

	unsigned getBucketIndex(unsigned num) const;
	bool inInterval(unsigned number) const;

public:
	DynamicSet();
	DynamicSet(const char* name, unsigned a, unsigned b, unsigned* numbers, size_t size);

	const char* getName() const;
	void setName(const char*);

	DynamicSet(const DynamicSet& other);
	DynamicSet& operator=(const DynamicSet& other);
	~DynamicSet();

	void invert(unsigned num);
	unsigned elementsCount() const;
	void clear();

	bool subset(const DynamicSet& other) const;

    void print() const;

	bool contains(unsigned num) const;
	DynamicSet UnionOfSets(const DynamicSet& rhs) const;
	DynamicSet IntersectionOfSets(const DynamicSet& rhs) const;
};
