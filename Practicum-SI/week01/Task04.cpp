#include <iostream>
#pragma warning(disable: 4996)
const int MAX_LEN_NAME = 16;
const double EPSILON = 0.00000001;
enum class Course {
	first,
	second,
	third,
	fourth,
	unknown
};
struct Student {
	Course course = Course::unknown;
	char name[MAX_LEN_NAME] = "";
	int fn = 10000;//from 10000 to 99999
	double avgGrade = 3.0; // from 3.0 to 6.0
};
void printStudent(const Student& toPrint) {
	switch (toPrint.course) {
	case Course::first:
		std::cout << "Course: first" << std::endl;
		break;
	case Course::second:
		std::cout << "Course: second" << std::endl;
		break;
	case Course::third:
		std::cout << "Course: third" << std::endl;
		break;
	case Course::fourth:
		std::cout << "Course: fourth" << std::endl;
		break;
	case Course::unknown:
		std::cout << "Course: unknown" << std::endl;
		break;
	}
	std::cout<< "Name: " << toPrint.name
	<< std::endl;
	std::cout << "FN: " << toPrint.fn
	<< std::endl;
	std::cout << "Average grade: " << toPrint.avgGrade
	<< std::endl;
}
double myAbs(double num) {
	if (num < 0) {
		return num * (-1);
	}
	return num;
}
void bubbleSortByGrade(Student* students, size_t len) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (students[j].avgGrade < students[j + 1].avgGrade) {
				std::swap(students[j], students[j + 1]);
			}
		}
	}
}
void printScholarsSorted(Student* students, size_t len, double average) {
	if (students != nullptr &&
		len > 0 &&
		(average > 3.0 || myAbs(average - 3.0) < EPSILON) &&
		(average < 6.0 || myAbs(average - 6.0) < EPSILON)) {
		bubbleSortByGrade(students, len);
		//print students sorted
		for (int i = 0; i < len; i++) {
			if (students[i].avgGrade > average) {
				printStudent(students[i]);
			}
			else {
				break;
			}
		}
	}
	else {
		std::cout << "Incorrect input" << std::endl;
	}
}

bool initStudent(Student& toInit,const char name[MAX_LEN_NAME],
	int  facNumber, Course currentCourse, double grade) {
	if (std::strlen(name) <= 15 &&
		facNumber >= 10000 &&
		facNumber < 99999 &&
		(grade > 3.0 || myAbs(grade - 3.0) < EPSILON) &&
		(grade < 6.0 || myAbs(grade - 6.0) < EPSILON)) {
		toInit.avgGrade = grade;
		toInit.course = currentCourse;
		toInit.fn = facNumber;
		std::strcpy(toInit.name, name);
		return true;
	}
	return false;
}
int main() {
	Student st0 = {Course::first, "asd", 12345, 5.1};
	Student st1 = { Course::second, "asd", 12346, 3.7};
	Student st2 = { Course::first, "asd", 12347, 3.4 };
	Student st3 = { Course::third, "asd", 12348, 5.4 };
	Student scholars[] = { st0, st1, st2, st3 };
	printScholarsSorted(scholars, 4, 3.6);
}