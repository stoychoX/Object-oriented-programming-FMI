#pragma once
#include <cstddef>
class Bitset
{
private:
	char* data = nullptr;
	size_t limit;
	size_t bucketsCount;

	void free();
	void copyFrom(const Bitset&);

	size_t bucketsNeeded(size_t n) const;
	size_t getBucket(size_t n) const;
	size_t getPosition(size_t n) const;
public:
	Bitset();
	Bitset(size_t n);

	void addNumber(size_t number);
	void removeNumber(size_t number) const;

	bool hasNumber(size_t number) const;

	void print() const;

	Bitset(const Bitset&);
	Bitset& operator=(const Bitset&);

	friend Bitset Union(const Bitset& lhs, const Bitset& rhs);
    friend Bitset Intersect(const Bitset& lhs, const Bitset& rhs);

	~Bitset();
};
