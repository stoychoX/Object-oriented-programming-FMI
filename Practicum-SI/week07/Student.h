#pragma once
#include <iostream>
#include <fstream>

class Student {
	char name[20]{};
	int fn = 0;
	double average = 0;

public:
	Student() = default;
	Student(const char* name, int fn, double average);

	const char* getName() const;
	int getFn() const;
	double getAverage() const;

	void saveStudentToFile(std::ofstream& ofs);
	void readStudentFromFile(std::ifstream& ifs);
};