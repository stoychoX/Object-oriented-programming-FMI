#include "Time.h"
#include <iostream>

Time::Time() : Time(0, 0, 0) {}

Time::Time(unsigned hours, unsigned minutes, unsigned seconds)
{
    setSeconds(seconds);
    setMinutes(minutes);
    setHours(hours);
}

Time::Time(unsigned secondsFromMidnight)
{
    initializeFromSeconds(secondsFromMidnight);
}

void Time::setHours(unsigned hours)
{
    if (hours >= 24)
        return;
    hrs = hours;
}
void Time::setMinutes(unsigned minutes)
{
    if (minutes >= 60)
        return;
    mins = minutes;
}
void Time::setSeconds(unsigned seconds)
{
    if (seconds >= 60)
        return;
    sec = seconds;
}

unsigned Time::getSecondsFromMidnight() const
{
    return 3600 * hrs + 60 * mins + sec;
}

Time Time::getTimeToMidnight() const
{
    unsigned midnightTimestamp = 24 * 3600;
    return Time(midnightTimestamp - getSecondsFromMidnight());
}

void Time::tick()
{
    initializeFromSeconds(getSecondsFromMidnight() + 1);
}

bool Time::greater(const Time &other) const
{
    return getSecondsFromMidnight() > other.getSecondsFromMidnight();
}

bool Time::lessThen(const Time &other) const
{
    return getSecondsFromMidnight() < other.getSecondsFromMidnight();
}

bool Time::isTimeForDinner() const
{
    Time lower(20, 30, 0);
    Time upper(22, 0, 0);

    return lessThen(upper) && !lessThen(lower);
}

Time Time::difference(const Time &other) const
{
    unsigned mySeconds = getSecondsFromMidnight();
    unsigned otherSeconds = other.getSecondsFromMidnight();

    if (mySeconds > otherSeconds)
        return Time(mySeconds - otherSeconds);
    return Time(otherSeconds - mySeconds);
}

void Time::print() const
{
    std::cout << hrs << " " << mins << " " << sec << std::endl;
}

void Time::initializeFromSeconds(unsigned secondsFromMidnight)
{
    if (secondsFromMidnight >= 24 * 3600)
        secondsFromMidnight = 0;

    setHours(secondsFromMidnight / 3600);
    secondsFromMidnight %= 3600;
    setMinutes(secondsFromMidnight / 60);
    secondsFromMidnight %= 60;
    setSeconds(secondsFromMidnight);
}
