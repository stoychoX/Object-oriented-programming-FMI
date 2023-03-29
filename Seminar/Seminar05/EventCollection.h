#pragma once
#include"Event.h"

class EventCollection {
private:
	Event data[20];
	uint8_t size;

	EventCollection eventsOnDate(const Date&) const;

public:
	EventCollection();

	bool addEvent(const Event&);

	uint8_t getSize() const;

	bool empty() const;
	bool full() const;

	EventCollection getMaxEvents(const Date&) const;

	const Event& getByIndex(size_t idx) const;
};