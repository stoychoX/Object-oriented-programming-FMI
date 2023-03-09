#include <iostream>
#pragma warning(disable : 4996)

enum class Course {
	first,
	second,
	third,
	forth
};

struct Student // 4 x 8 bytes?
{
	char name[16];
	int fn;
	Course course;
	double avgGrade;
};

char* GetCourse(const Student& toPrint)
{
	char* course = new char[10];
	switch (toPrint.course)
	{
	case Course::first:
		strcpy(course, "first");
		break;
	case Course::second:
		strcpy(course, "second");
		break;
	case Course::third:
		strcpy(course, "third");
		break;
	case Course::forth:
		strcpy(course, "forth");
		break;
	default:
		strcpy(course, "invalid");
		break;
	}
	return course;
}

void printStudent(const Student& toPrint)
{
	std::cout << toPrint.name << " with fn: " << toPrint.fn << " from "
		<< GetCourse(toPrint) << " course with grade: " << toPrint.avgGrade << std::endl;
}

inline bool CheckGrade(const double& grade)
{
	return (grade >= 3.00 && grade <= 6.00);
}

bool initStudent(Student& toInit, char name[16], int facNumber, Course currentCourse, double grade)
{
	//what else to check?
	if (CheckGrade(grade))
	{
		strcpy(toInit.name, name);
		toInit.fn = facNumber;
		toInit.course = currentCourse;
		toInit.avgGrade = grade;
		return true;
	}
	return false;
}

void sortStudents(Student* students, int countStudentsInList)
{
	for (size_t i = 0; i < countStudentsInList - 1; i++)
	{
		for (size_t j = i + 1; j < countStudentsInList; j++)
		{
			if (students[i].avgGrade < students[j].avgGrade)
			{
				std :: swap(students[i], students[j]);
			}
		}
	}
}

void printScholars(const Student* students, size_t length, double average)
{
	Student* studentsAboveAvg = new Student[length];
	int countStudentsAboveAvg = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (students[i].avgGrade >= average)
		{
			studentsAboveAvg[countStudentsAboveAvg] = students[i];
			countStudentsAboveAvg++;
		}
	}

	sortStudents(studentsAboveAvg, countStudentsAboveAvg);
	for (size_t i = 0; i < countStudentsAboveAvg; i++)
	{
		printStudent(studentsAboveAvg[i]);
	}

	delete[] studentsAboveAvg;
}

int main()
{
	Student a;
	Student b;
	Student c;
	char* nameA = new char[16]{"dani"};
	char* nameB = new char[16]{"kolio"};
	char* nameC = new char[16] {"nasko"};
	initStudent(a, nameA, 123499999, Course::first, 5);
	initStudent(b, nameB, 1235, Course::third, 4.55);
	initStudent(c, nameC, 1236, Course::second, 5.00);
	Student* st = new Student[3]{a,b,c};
	printScholars(st, 3, 3.00);
}
