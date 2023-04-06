#include "Group.h"
#include "Student.h"
#include <cstring>

void Group::resize() {
	capacity = capacity * 2;
	Student* newArr = new Student[capacity];

	for (size_t i = 0; i < count; i++)
	{
		newArr[i] = students[i];
	}

	delete[] students;
	students = newArr;
}

void Group::copyStudents(const Student* newStudents, size_t len) {
	students = new Student[len];
	count = len;

	for (size_t i = 0; i < len; i++)
	{
		students[i] = newStudents[i];
	}
}

void Group::copyFrom(const Group& other) {
	copyStudents(other.students, other.count);
}

void Group::free() {
	delete[] students;
	students = nullptr;
	count = 0;
}

Group::Group(const Group& students) {
	copyFrom(students);
}

Group& Group::operator=(const Group& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Group::~Group() {
	free();
}

void Group::addStudent(const Student& student) {
	if (count == capacity)
	{
		resize();
	}
	students[count++] = student;
}

double Group::getAverageGrades() const {
	double gradeAverage = 0;

	for (size_t i = 0; i < count; i++)
	{
		gradeAverage += students[i].getAverage();
	}

	return gradeAverage;
}

void Group::saveToBinaryFile(std::ofstream& ofs) {

	if (count == 0)
		return;

	for (size_t i = 0; i < count; i++)
	{
		students[i].saveStudentToFile(ofs);
	}
}

void Group::readFromBinaryFile(std::ifstream& ifs) {
	if (count == 0)
		return;

	for (size_t i = 0; i < count; i++)
	{
		students[i].readStudentFromFile(ifs);
	}
}
