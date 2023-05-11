#include "Student.h"
#include <iostream>
#pragma warning(disable : 4996)

void Student::copyFrom(const Student& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	fn = other.fn;
	avGrade = other.avGrade;
}
void Student::free()
{
	delete[] name;
	fn = avGrade = 0;
}

Student::Student(const char* name, int fn, double avGrade)
{
	if (name == nullptr)
	{
		std::cout << "Invalid name! Name set to \"default\"\n";
		size_t nameLen = strlen("default");
		this->name = new char[nameLen + 1];
		strcpy(this->name, "default");
		this->name[nameLen] = '\0';
	}
	else
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->fn = fn;
		this->avGrade = avGrade;
	}
}
Student::Student(const Student& other)
{
	copyFrom(other);
}
Student& Student::operator=(const Student& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Student::~Student()
{
	free();
}
const char* Student::getName() const
{
	return name;
}
int Student::getFn() const
{
	return fn;
}
double Student::getAvGrade() const
{
	return avGrade;
}
void Student::writeToBinary(std::ofstream& ofs) const
{
	if (!ofs.is_open())
	{
		std::cout << "File not open!\n";
		return;
	}
	size_t nameLength = strlen(name);
	ofs.write((const char*)&nameLength, sizeof(nameLength));
	ofs.write(name, nameLength);
	ofs.write((const char*)&fn, sizeof(fn));
	ofs.write((const char*)&avGrade, sizeof(avGrade));
}
void Student::readFromBinary(std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		std::cout << "File not open!\n";
		return;
	}
	free();
	size_t nameLength = 0;
	ifs.read((char*)&nameLength, sizeof(nameLength));
	name = new char[nameLength + 1];
	ifs.read(name, nameLength);
	name[nameLength] = '\0';
	ifs.read((char*)&fn, sizeof(fn));
	ifs.read((char*)&avGrade, sizeof(avGrade));
}
void Student::print() const
{
	std::cout << name << " " << fn << " " << avGrade << "\n";
}