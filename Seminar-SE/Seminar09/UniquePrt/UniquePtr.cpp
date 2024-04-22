#include "UniquePtr.h"
#include <utility>

UniquePtr::UniquePtr(A* arg) : ptr(arg) {}

A& UniquePtr::operator*()
{
	return *ptr;
}

const A& UniquePtr::operator*() const
{
	return *ptr;
}

A* UniquePtr::operator->()
{
	return ptr;
}

const A* UniquePtr::operator->() const
{
	return ptr;
}

A* UniquePtr::get()
{
	return ptr;
}

void UniquePtr::reset(A* nPtr)
{
	free();
	ptr = nPtr;
}

A* UniquePtr::release()
{
	A* toReturn = ptr;
	ptr = nullptr;
	return toReturn;
}

UniquePtr::UniquePtr(UniquePtr&& other) noexcept
{
	move(std::move(other));
}

UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

UniquePtr::~UniquePtr()
{
	free();
}

void UniquePtr::move(UniquePtr&& other)
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

void UniquePtr::free()
{
	delete ptr;
}