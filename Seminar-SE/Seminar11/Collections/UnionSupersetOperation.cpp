#include "UnionSupersetOperation.h"

UnionSupersetOperation::UnionSupersetOperation(
	const Collection& left, 
	const Collection& right) :
	CollectionSupersetOperation(left, right)
{
}

void UnionSupersetOperation::add(int arg)
{
	dummy.add(arg);
}

void UnionSupersetOperation::remove(int arg)
{
	dummy.remove(arg);
}

size_t UnionSupersetOperation::count(int arg) const
{
	return left.count(arg) + right.count(arg) + dummy.count(arg);
}

bool UnionSupersetOperation::contains(int arg) const
{
	return left.count(arg) || right.count(arg) || dummy.count(arg);;
}
