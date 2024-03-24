#pragma once

#include "Date.h"
#include "Time.h"

typedef BulgarianDate Date;

class Event
{
private:
    char name[21]{};
    Date date;
    Time start;
    Time end;

    void setName(const char* name);
    void validateTime();
public:
    Event() = default;

    Event(
        const char* name,
        unsigned day, unsigned mount, unsigned year,
        unsigned hoursStart, unsigned minutesStart, unsigned secondsStart,
        unsigned hoursEnd, unsigned minutesEnd, unsigned secondsEnd
    );

    Event(
        const char* name,
        const Date& date,
        const Time& start,
        const Time& end
    );

    const Date& getDate() const;
    const char* getName() const;
    const Time& getStart() const;
    const Time& getEnd() const;

    Time getLenght() const;

    void print() const;
};
