#include "Student.h"
#include <cstring>

Student::Student(const char* name, int fn, double average) {
	if (strlen(name) <= 20)
	{
		strcpy_s(this->name, name);
	}
	this->fn = fn;
	this->average = average;
}

const char* Student::getName() const {
	return name;
}
int Student::getFn() const {
	return fn;
}
double Student::getAverage() const {
	return average;
}

void Student::saveStudentToFile(std::ofstream& ofs) {
	//ofs.write(name, 20);
	//ofs.write((const char*)&fn, sizeof(fn));
	//ofs.write((const char*)&average, sizeof(average));

	ofs.write((const char*)this, sizeof(Student));
}

void Student::readStudentFromFile(std::ifstream& ifs) {
	//ifs.read(name, 20);
	//ifs.read((char*)&fn, sizeof(fn));
	//ifs.read((char*)&average, sizeof(average));

	ifs.read((char*)this, sizeof(Student));
}
