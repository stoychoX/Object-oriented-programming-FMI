#include "Event.h"
#include <cstring>
#include <utility>  // std::swap
#include <iostream>

void Event::setName(const char* arg)
{
	unsigned len = strlen(arg);
	if (len > 20)
		return;
	strcpy(name, arg);
}

void Event::validateTime()
{
	if (start.greater(end))
		std::swap(start, end);
}

Event::Event(
	const char* name, 
	unsigned day, unsigned mount, unsigned year, 
	unsigned hoursStart, unsigned minutesStart, unsigned secondsStart, 
	unsigned hoursEnd, unsigned minutesEnd, unsigned secondsEnd) :
	date(day, mount, year),
	start(hoursStart, minutesStart, secondsStart),
	end(hoursEnd, minutesEnd, secondsEnd)
{
	setName(name);
}

Event::Event(
	const char* name, 
	const Date& date, 
	const Time& start, 
	const Time& end) :
	date(date),
	start(start),
	end(end)
{
	setName(name);
}

const Date& Event::getDate() const
{
	return date;
}

const char* Event::getName() const
{
	return name;
}

const Time& Event::getStart() const
{
	return start;
}

const Time& Event::getEnd() const
{
	return end;
}

Time Event::getLenght() const
{
	return start.difference(end);
}

void Event::print() const
{
	std::cout << name << ": " << std::endl << "At: ";
	date.print();
	std::cout << "From: ";
	start.print();
	std::cout << "To: ";
	end.print();
}