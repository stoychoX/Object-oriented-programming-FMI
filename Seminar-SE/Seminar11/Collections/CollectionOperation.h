#pragma once
#include "Collection.h"

class CollectionOperation : public Collection
{
protected:
	const Collection& left;
	const Collection& right;

public:
	CollectionOperation(const Collection& l, const Collection& r);
};

