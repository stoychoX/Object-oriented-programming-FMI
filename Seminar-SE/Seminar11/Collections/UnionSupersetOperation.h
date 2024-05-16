#pragma once
#include "CollectionSupersetOperation.h"
#include "Collection.h"

class UnionSupersetOperation 
	: public CollectionSupersetOperation
{
public:
	UnionSupersetOperation(const Collection& left, const Collection& right);

	virtual void add(int) override;
	virtual void remove(int) override;
	virtual size_t count(int) const override;
	virtual bool contains(int) const override;
};

