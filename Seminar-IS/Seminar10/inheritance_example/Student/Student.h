#pragma once
#include "../Person/Person.h"

class Student : public Person
{
private:
	unsigned facNum;
public:
	Student(
		const char* name, 
		unsigned age,
		unsigned facNum);

	unsigned getFacNum() const;
};

