#include "Event.h"

void Event::validateTimes() {
    if (begin.compare(end) == 1)
        std::swap(begin, end);
}

Event::Event() :
    name{""},
    date(1,1, 1970),
    begin(0, 0, 0),
    end(23,59, 59) {}

Event::Event(const char* argName, const Date& argDate, const Time& argBeg, const Time& argEnd) :
    name{""}, date(argDate), begin(argBeg), end(argEnd) {
    setName(argName);
}

Event::Event
( // arguments:
    const char* argName, 
    unsigned day, unsigned month, unsigned year, 
    size_t bhours, size_t bmins, size_t bseconds, 
    size_t ehours, size_t emins, size_t eseconds
) : //initializer list:
    name{""}, 
    date(day, month, year),
    begin(bhours, bmins, bseconds),
    end(ehours, emins, eseconds) 
{
    setName(argName);
    validateTimes();
}

const char* Event::getName() const {
    return name;
}

const Date& Event::getDate() const {
    return date;
}

const Time& Event::getBegin() const {
    return begin;
}

const Time& Event::getEnd() const {
    return end;
}

void Event::setName(const char* argName) {
    if (strlen(argName) > 20)
        return;

    strcpy(name, argName);
}