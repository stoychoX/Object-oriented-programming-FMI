#pragma once
#include<cstddef>

class Bitset {
private:
	unsigned char* data;
	size_t maxNumbers;

	size_t getBucketCount() const;
	size_t getMask(size_t number) const;
	size_t getBucket(size_t number) const;

public:
	Bitset(size_t maxNum);

	Bitset(const Bitset& other);
	Bitset& operator=(const Bitset& other);

	void addNumber(size_t number);
	bool contains(size_t number) const;
	void removeNumber(size_t number);

	// Remove every element from the bitset
	void erase();

	Bitset unionBitset(const Bitset& other) const;
	Bitset intersectBitset(const Bitset& other) const;
	Bitset compliment() const;

	size_t getMaxNumber() const;

	~Bitset();

private:
	void free();
	void copyFrom(const Bitset& other);
};