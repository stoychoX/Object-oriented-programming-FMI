#include "Group.h"
#include <iostream>
#include <fstream>

namespace
{
	int getClosestPowerOfTwo(int num)
	{

		num--;
		num |= num >> 1;
		num |= num >> 2;
		num |= num >> 4;
		num |= num >> 8;
		num |= num >> 16;
		num++;
		return num;
	}
}
void Group::copyFrom(const Group& other)
{
	students = new Student[other.students_count];
	students_count = other.students_count;
	capacity = getClosestPowerOfTwo(students_count);
}

void Group::free()
{
	delete[] students;
	students_count = 0;
	capacity = 1;
}

Group::Group(const Student* students, size_t count)
{
	if (students == nullptr)
	{
		std::cout << "Invalid students! Group not created!\n";
	}
	else
	{
		this->students = new Student[count];
		for (size_t i = 0; i < count; i++)
		{
			this->students[i] = students[i];
		}
		students_count = count;
		capacity = getClosestPowerOfTwo(count);
	}
}
Group::Group(const Group& other)
{
	copyFrom(other);
}
Group& Group::operator=(const Group& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Group::~Group()
{
	free();
}

size_t Group::getCountStudents() const
{
	return students_count;
}

namespace
{
	void resize(Student*& students, size_t count, size_t capacity)
	{
		Student* newStudents = new Student[capacity];
		for (size_t i = 0; i < count; i++)
		{
			newStudents[i] = students[i];
		}
		delete[] students;
		students = newStudents;
	}
}
void Group::addStudent(const Student& st)
{
	if (students_count == capacity)
	{
		capacity *= 2;
		resize(students, students_count, capacity);
	}
	students[students_count++] = st;
}
double Group::getAvGroupGrade() const
{
	double avGrRate = 0.0;
	for (size_t i = 0; i < students_count; i++)
	{
		avGrRate += students[i].getAvGrade();
	}
	return avGrRate / (double)students_count;
}
void Group::safeToBinary(const char* fileName) const
{
	if (fileName != nullptr)
	{
		std::ofstream ofs(fileName, std::ios::binary);
		if (!ofs.is_open())
		{
			std::cout << "File not open!\n";
			return;
		}
		ofs.write((const char*)&students_count, sizeof(students_count));
		for (size_t i = 0; i < students_count; i++)
		{
			students[i].writeToBinary(ofs);
		}
		ofs.close();
	}
}
void Group::getGroupFromBinary(const char* fileName)
{
	if (fileName != nullptr)
	{
		std::ifstream ifs(fileName, std::ios::binary);
		if (!ifs.is_open())
		{
			std::cout << "File not open!\n";
			return;
		}
		size_t countStudents = 0;
		ifs.read((char*)&countStudents, sizeof(countStudents));
		delete[] students;
		students = new Student[countStudents];
		for (size_t i = 0; i < countStudents; i++)
		{
			students[i].readFromBinary(ifs);
		}
		ifs.close();
	}
}
void Group::print() const
{
	for (size_t i = 0; i < students_count; i++)
	{
		students[i].print();
	}
}