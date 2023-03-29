#include "EventCollection.h"
#include<exception>

EventCollection EventCollection::eventsOnDate(const Date& argDate) const {
	EventCollection sameDateBuffer;
	
	for (size_t i = 0; i < size; i++) {
		if (argDate.isEqualTo(data[i].getDate())) {
			sameDateBuffer.addEvent(data[i]);
		}
	}

	return sameDateBuffer;
}

EventCollection::EventCollection() : size{0} {}

bool EventCollection::addEvent(const Event& e) {
	if (size == 20)
		return false;

	data[size++] = e;
	return true;
}

uint8_t EventCollection::getSize() const {
	return size;
}

bool EventCollection::empty() const {
	return size == 0;
}

bool EventCollection::full() const {
	return size == 20;
}

EventCollection EventCollection::getMaxEvents(const Date& argDate) const {
	EventCollection sameDateBuffer = eventsOnDate(argDate);
	
	// За да е по - четим кодът вземам референция
	// към масива, който ще сортирам
	Event(&sameDateData)[20] = sameDateBuffer.data;

	// Сортираме ги по време на приключване
	for (size_t i = 0; i < size - 1; i++) {
		size_t currMinIndex = i;

		for (size_t j = i + 1; j < size; j++) {
			if (sameDateData[currMinIndex].getEnd().compare(sameDateData[j].getEnd()) == 1) {
				currMinIndex = j;
			}
		}

		if (currMinIndex != i) {
			std::swap(sameDateData[currMinIndex], sameDateData[i]);
		}
	}

	
	EventCollection toReturn;
	toReturn.addEvent(sameDateData[0]);

	// Ако началото на това събитие е по - късно от края на последното 
	// добавено събитие го добави в колекцията.
	for (size_t i = 1; i < sameDateBuffer.size; i++) {
		if (sameDateData[i].getBegin().compare(toReturn.data[toReturn.size - 1].getEnd()) >= 0) {
			toReturn.addEvent(sameDateBuffer.data[i]);
		}
	}

	return toReturn;
}

const Event& EventCollection::getByIndex(size_t idx) const {
	if (idx >= size)
		throw std::exception("Invalid index");

	return data[idx];
}
