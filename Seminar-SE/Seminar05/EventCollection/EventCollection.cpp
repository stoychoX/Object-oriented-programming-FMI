#include "EventCollection.h"
#include <utility>
#include <cstring>
#include <assert.h>

void EventManager::addEvent(const Event& event)
{
	if (size == 20)
		return;

	events[size++] = event;
}

void EventManager::removeLast()
{
	if (empty())
		return;
	size--;
}

void EventManager::remove(const char* name)
{
	int nameIdx = find(name);

	if (nameIdx == -1)
		return;
	std::swap(events[nameIdx], events[size - 1]);

	removeLast();
}

const Event& EventManager::at(size_t index) const
{
    assert(index < size);
    return events[index];
}


int EventManager::find(const char* name) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(events[i].getName(), name) == 0)
			return i;
	}
	return -1;
}

int EventManager::longestEventIndex() const
{
	if (empty())
		return -1;

	Time maxLenght = events[0].getLenght();
	int index = 0;
	for (size_t i = 1; i < size; i++)
	{
		Time currentLen = events[i].getLenght();
		if (currentLen.greater(maxLenght))
		{
			index = i;
			maxLenght = currentLen;
		}
	}
	return index;
}

bool EventManager::empty() const
{
	return (size == 0);
}
