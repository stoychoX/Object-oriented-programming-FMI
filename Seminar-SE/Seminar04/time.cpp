#include <iostream>

class Time
{
public:
    Time() : Time(0, 0, 0) {}

    Time(unsigned hours, unsigned minutes, unsigned seconds)
    {
        setSeconds(seconds);
        setMinutes(minutes);
        setHours(hours);
    }

    Time(unsigned secondsFromMidnight)
    {
        initializeFromSeconds(secondsFromMidnight);
    }

    void setHours(unsigned hours)
    {
        if (hours >= 24)
            return;
        hrs = hours;
    }
    void setMinutes(unsigned minutes)
    {
        if (minutes >= 60)
            return;
        mins = minutes;
    }
    void setSeconds(unsigned seconds)
    {
        if (seconds >= 60)
            return;
        sec = seconds;
    }

    unsigned getSecondsFromMidnight() const
    {
        return 3600 * hrs + 60 * mins + sec;
    }

    Time getTimeToMidnight() const
    {
        unsigned midnightTimestamp = 24 * 3600;
        return Time(midnightTimestamp - getSecondsFromMidnight());
    }

    void tick()
    {
        initializeFromSeconds(getSecondsFromMidnight() + 1);
    }

    bool lessThen(const Time &other) const
    {
        return getSecondsFromMidnight() < other.getSecondsFromMidnight();
    }

    bool isTimeForDinner() const
    {
        Time lower(20, 30, 0);
        Time upper(22, 0, 0);

        return lessThen(upper) && !lessThen(lower);
    }

    Time difference(const Time &other) const
    {
        unsigned mySeconds = getSecondsFromMidnight();
        unsigned otherSeconds = other.getSecondsFromMidnight();

        if (mySeconds > otherSeconds)
            return Time(mySeconds - otherSeconds);
        return Time(otherSeconds - mySeconds);
    }

    void print() const
    {
        std::cout << hrs << " " << mins << " " << sec << std::endl;
    }
private:
    void initializeFromSeconds(unsigned secondsFromMidnight)
    {
        if (secondsFromMidnight >= 24 * 3600)
            secondsFromMidnight = 0;

        setHours(secondsFromMidnight / 3600);
        secondsFromMidnight %= 3600;
        setMinutes(secondsFromMidnight / 60);
        secondsFromMidnight %= 60;
        setSeconds(secondsFromMidnight);
    }
    unsigned hrs = 0;
    unsigned mins = 0;
    unsigned sec = 0;
};

int main()
{
    Time t(18, 25, 0);
    t.print();

    Time mid = t.getTimeToMidnight();
    std::cout << "Time to midnight: ";
    mid.print();
}