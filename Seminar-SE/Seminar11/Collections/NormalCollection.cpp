#include "NormalCollection.h"
#include <utility>

void NormalCollection::add(int arg)
{
	if (size == capacity)
	{
		resize(2 * size);
	}
	data[size++] = arg;
}

void NormalCollection::remove(int arg)
{
	if (size == 0)
		return;

	int idx = -1;
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == arg)
		{
			idx = i;
			break;
		}
	}

	if (idx != -1)
		std::swap(data[idx], data[--size]);
}

size_t NormalCollection::count(int arg) const
{
	unsigned cnt = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == arg)
		{
			++cnt;
		}
	}

	return cnt;
}

bool NormalCollection::contains(int arg) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == arg)
			return true;
	}
	return false;
}
