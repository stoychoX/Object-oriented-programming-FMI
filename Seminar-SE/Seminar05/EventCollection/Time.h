#pragma once

class Time
{
public:
    Time();
    Time(unsigned hours, unsigned minutes, unsigned seconds);
    Time(unsigned secondsFromMidnight);
    
    void setHours(unsigned hours);
    void setMinutes(unsigned minutes);
    void setSeconds(unsigned seconds);

    unsigned getSecondsFromMidnight() const;

    Time getTimeToMidnight() const;

    void tick();

    bool greater(const Time& other) const;

    bool lessThen(const Time& other) const;

    bool isTimeForDinner() const;

    Time difference(const Time& other) const;
    
    void print() const;
private:
    void initializeFromSeconds(unsigned secondsFromMidnight);
    unsigned hrs = 0;
    unsigned mins = 0;
    unsigned sec = 0;
};