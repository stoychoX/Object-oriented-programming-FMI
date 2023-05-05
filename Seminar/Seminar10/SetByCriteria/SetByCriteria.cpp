#include "SetByCriteria.h"
#include<iostream>

void SetByCriteria::initSet() {
	Bitset::erase();

	for (size_t i = 0; i < Bitset::getMaxNumber(); i++) {
		if (mCriteria.incl(i) && !mCriteria.excl(i)) {
			Bitset::addNumber(i);
		}
	}
}

SetByCriteria::SetByCriteria(size_t n, Criteria c) : Bitset(n), mCriteria(c) {
	initSet();
}

void SetByCriteria::setInclude(predicate incl) {
	mCriteria.incl = incl;
	initSet();
}

void SetByCriteria::setExclude(predicate excl) {
	mCriteria.excl = excl;
	initSet();
}

bool SetByCriteria::contains(unsigned i) const {
	return Bitset::contains(i);
}

void SetByCriteria::print() const {
	for (size_t i = 0; i < Bitset::getMaxNumber(); i++) {
		if (contains(i)) {
			std::cout << i << " ";
		}
	}
}