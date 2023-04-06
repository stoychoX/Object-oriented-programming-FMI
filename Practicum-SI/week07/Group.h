#pragma once
#include "Student.h"
#include <iostream>

class Group {
	Student* students = nullptr;
	size_t count = 0;
	size_t capacity = 0;

	void resize();
	void copyStudents(const Student* newStudents, size_t count);

	void copyFrom(const Group& other);
	void free();

public:
	Group() = default;
	Group(const Group& students);
	Group& operator=(const Group& other);
	~Group();

	void addStudent(const Student& student);
	double getAverageGrades() const;

	void saveToBinaryFile(std::ofstream& ofs);
	void readFromBinaryFile(std::ifstream& ifs);
};