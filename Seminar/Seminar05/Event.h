#pragma once
#include"Date/Date.h"
#include"Time/Time.h"
#include<cstring>

#pragma warning(disable : 4996)

class Event {
private:
	char name[21];
	Date date;
	Time begin;
	Time end;

	void validateTimes();
	void setName(const char*);
public:
	Event();

	Event(const char* argName, const Date& argDate, const Time& argBeg, const Time& argEnd);

	Event(
		const char* argName,
		unsigned day, unsigned month, unsigned year,	// Date constr
		size_t bhours, size_t bmins, size_t bseconds,	// beg time constr
		size_t hours, size_t mins, size_t seconds		// end time constr
		);

	
	// get:
	const char* getName() const;
	const Date& getDate() const;
	const Time& getBegin() const;
	const Time& getEnd() const;
};

