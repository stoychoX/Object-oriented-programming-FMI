#pragma once
#include "Student.h"
class Group
{
	Student* students = nullptr;
	size_t students_count = 0;
	size_t capacity = 1;
	void copyFrom(const Group& other);
	void free();
public:
	Group(const Student* students, size_t count);
	Group(const Group& other);
	Group& operator=(const Group& other);
	~Group();

	size_t getCountStudents() const;
	void addStudent(const Student& st);
	double getAvGroupGrade() const;
	void safeToBinary(const char* fileName) const;
	void getGroupFromBinary(const char* fileName);
	void print() const;
};
