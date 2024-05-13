#pragma once
#include "../Person/Person.h"
#include <cstddef>

class Teacher : public Person
{
private:
	char** subjects = nullptr;
	unsigned subjectsLen = 0;

	char* copyString(const char* oldString) const;


	void copyFrom(const Teacher&);
	void free();

	void move(Teacher&&);
public:
	Teacher();

	Teacher(
		const char* name,
		unsigned age,
		const char* const * subjects,
		unsigned subjectsLen
	);

	Teacher(const Teacher&);
	Teacher(Teacher&&);

	Teacher& operator=(const Teacher&);
	Teacher& operator=(Teacher&&);

	const char* operator[](size_t idx) const;

	~Teacher();
};

