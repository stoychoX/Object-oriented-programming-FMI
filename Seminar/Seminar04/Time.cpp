#include<iostream>

class Time {
private:
	unsigned hrs;
	unsigned mins;
	unsigned seconds;

	bool isInInterval(size_t from, size_t to, size_t arg) const {
		return arg >= from && arg <= to;
	}

	void fromUnixTime(size_t uTime) {
		uTime = uTime % (24 * 60 * 60);

		setHours(uTime / 3600);
		size_t rest = uTime % 3600;
		setMinutes(rest / 60);
		setSeconds(rest % 60);
	}

public:
	Time() : Time(0, 0, 0) {}

	Time(unsigned arghrs, unsigned argmins, unsigned argsecond) {
		setHours(arghrs);
		setMinutes(argmins);
		setSeconds(argsecond);
	}

	Time(size_t unixTime) {
		fromUnixTime(unixTime);
	}

	void setHours(unsigned hours) {
		if (isInInterval(0, 23, hours))
			hrs = hours;
	}

	void setMinutes(unsigned minutes) {
		if (isInInterval(0, 59, minutes))
			mins = minutes;
	}

	void setSeconds(unsigned s) {
		if (isInInterval(0, 59, s))
			seconds = s;
	}

	unsigned getHours() const {
		return hrs;
	}

	unsigned getMinutes() const {
		return mins;
	}

	unsigned getSeconds() const {
		return seconds;
	}

	unsigned getUnixTime() const {
		return 3600 * hrs + 60 * mins + seconds;
	}

	Time timeUntilMidnight() const {
		unsigned midNight = 24 * 60 * 60;

		unsigned timeLeft = midNight - getUnixTime();

		return Time(timeLeft);
	}

	void increment() {
		size_t uTime = getUnixTime();
		uTime++;
		fromUnixTime(uTime);
	}

	void print() const {
		std::cout << hrs << ":" << mins << ":" << seconds << std::endl;
	}

    // Връща дали текущия час е по - рано
    // от подадения като параметър
	bool earlier(const Time& other) const {
		return getUnixTime() < other.getUnixTime();
	}

	bool isTimeForDinner() const {
		Time from(20, 30, 0);
		Time to(22, 0, 0);

		return earlier(from) && !earlier(to);
	}
};

int main() {
	Time t(23, 59, 57);
	
	t.increment();
	t.increment();
	t.increment();

    t.print();
}