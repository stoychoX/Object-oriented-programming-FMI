#pragma once
#include "CollectionOperation.h"
#include "NormalCollection.h"

class CollectionSupersetOperation :
	public CollectionOperation
{
protected:
	CollectionSupersetOperation(const Collection& l, const Collection& r);
	NormalCollection dummy;
};

