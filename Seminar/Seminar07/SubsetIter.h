#pragma once
#include"Bitset/Bitset.h"
#include<iostream>
class SubsetIter {
private:
	const int* data;
	size_t size;

	Bitset subsets;
public:
	SubsetIter(const int* arg, size_t size);

	SubsetIter& operator++();

	friend std::ostream& operator<<(std::ostream&, const SubsetIter&);
};

std::ostream& operator<<(std::ostream&, const SubsetIter&);