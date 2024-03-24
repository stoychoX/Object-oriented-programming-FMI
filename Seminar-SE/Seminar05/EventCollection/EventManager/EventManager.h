#pragma once
#include "../Event/Event.h"
#include <cstddef> // size_t

class EventManager
{
private:
	Event events[20];
	size_t size;
public:
	void addEvent(const Event& event);
	void removeLast();

	void remove(const char* name);
	int find(const char* name) const;

    const Event& at(size_t index) const;

	int longestEventIndex() const;

	bool empty() const;
};

