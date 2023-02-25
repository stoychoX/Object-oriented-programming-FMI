#include <iostream>

enum class Course {
	first,
	second,
	third,
	fourth
};

//(x64) this struct is always 32 bytes, independent from order of fields, because it has 0 padding bytes
struct Student {
	char name[16];
	int fn;
	Course course;
	double grade;
};

void printStudent(const Student& toPrint) {
	std::cout << "Name: " << toPrint.name << std::endl;
	std::cout << "Faculty number: " << toPrint.fn << std::endl;

	std::cout << "Course: ";
	switch (toPrint.course) {
	case Course::first: std::cout << "First"; break;
	case Course::second: std::cout << "Second"; break;
	case Course::third: std::cout << "Third"; break;
	case Course::fourth: std::cout << "Fourth"; break;
	}
	std::cout << std::endl;

	std::cout << "Grade: " << toPrint.grade << std::endl;
}

bool initStudent(Student& toInit,char name[16], int facNumber, Course currentCourse, double grade) {
	if (name[0] == '\0' || facNumber < 10000 || facNumber > 99999 || grade < 3 || grade > 6) {
		return false;
	}
	strcpy_s(toInit.name, name);
	toInit.fn = facNumber;
	toInit.course = currentCourse;
	toInit.grade = grade;
	return true;
}

void swapStudents(Student& one, Student& two) {
	char arr[16];
	strcpy_s(arr, one.name);
	strcpy_s(one.name, two.name);
	strcpy_s(two.name, arr);

	int temp = one.fn;
	one.fn = two.fn;
	two.fn = temp;

	Course c = one.course;
	one.course = two.course;
	two.course = c;

	double gr = one.grade;
	one.grade = two.grade;
	two.grade = gr;
}

void SortStudents(Student* students, size_t length) {
	for (size_t i = 0; i < length - 1; i++) {
		size_t max = i;
		for (size_t j = i + 1; j < length; j++) {
			if (students[j].grade > students[max].grade) {
				max = j;
			}
		}
		swapStudents(students[i],students[max]);
	}
}

void printScholars(Student* students, size_t length, double average) {
	SortStudents(students,length);
	size_t i = 0;
	while (students[i].grade > average) {
		std::cout << "Student " << (i + 1) << ":" << std::endl;
		printStudent(students[i]);
		i++;
	}
}
