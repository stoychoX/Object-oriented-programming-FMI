#pragma once
#include <fstream>
class Student
{
	char* name = nullptr;
	int fn = 0;
	double avGrade = 0.0;
	void copyFrom(const Student& other);
	void free();
public:
	Student() = default;
	Student(const char* name, int fn, double avGrade);
	Student(const Student& other);
	Student& operator=(const Student& other);
	~Student();
	const char* getName() const;
	int getFn() const;
	double getAvGrade() const;
	void writeToBinary(std::ofstream& ofs) const;
	void readFromBinary(std::ifstream& ifs);
	void print() const;
};