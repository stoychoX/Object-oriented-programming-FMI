#pragma once
#include"../../../Seminar/Seminar06/Bitset/Bitset.h"
#include<cstddef>

class SetByCriteria : private Bitset {
private:
	using predicate = bool (*)(unsigned);

	struct Criteria {
		Criteria(predicate _incl, predicate _excl) : incl(_incl), excl(_excl) {}

		predicate incl;
		predicate excl;
	};

	Criteria mCriteria;

	void initSet();
public:
	SetByCriteria(size_t n, Criteria c);

	static Criteria makeCriteria(predicate _incl, predicate _excl) {
		return Criteria(_incl, _excl);
	}

	void setInclude(predicate incl);
	void setExclude(predicate excl);

	bool contains(unsigned i) const;

	void print() const;
};