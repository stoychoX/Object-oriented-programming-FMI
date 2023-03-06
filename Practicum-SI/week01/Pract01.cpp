#include <iostream>
#pragma warning (disable:4996)
//Task04

//enum class Course {
//    first = 1,
//    second = 2,
//    third = 3,
//    forth = 4,
//    intializator = 0
//};
//
//struct Student
//{
//    char name[16] = "Invalid Input";
//    int fn = 0;
//    Course course = Course::intializator;
//    double averageGrade = 0;
//};
//
//int lengthOfInt(int num)
//{
//    int counter = 0;
//    while (num != 0)
//    {
//        num /= 10;
//        counter++;
//    }
//    return counter;
//}
//
//bool initStudent(Student& toInit,const char name[16], int facNumber, Course currentCourse, double grade)
//{
//    int lengthOfFN = lengthOfInt(facNumber);
//    if (strlen(name) > 16 || strlen(name) < 1)
//    {
//        return false;
//    }
//    else if (lengthOfFN != 5)
//    {
//        return false;
//    }
//    else if ((int)currentCourse > 4 || (int)currentCourse < 1)
//    {
//        return false;
//    }
//    else if (grade > 6 || grade < 2)
//    {
//        return false;
//    }
//    else
//    {
//        strcpy_s(toInit.name, name);
//        toInit.fn = facNumber;
//        toInit.course = currentCourse;
//        toInit.averageGrade = grade;
//    }
//}
//
//void printStudent(const Student& stud)
//{
//    std::cout << "Name: " << stud.name << std::endl;
//    std::cout << "Faculty Number: " << stud.fn << std::endl;
//    std::cout << "Course: " << (int)stud.course << std::endl;
//    std::cout << "Average Grade: " << stud.averageGrade << std::endl;
//}
//
//void sortStudents(Student* students, size_t length)
//{
//    for (int i = 0; i < length - 1; i++)
//    {
//        int maxGradeIndex = i;
//        for (int j = i; j < length; j++)
//        {
//            if (students[j].averageGrade > students[maxGradeIndex].averageGrade)
//            {
//                maxGradeIndex = j;
//            }
//        }
//        if (maxGradeIndex != i)
//        {
//            std::swap(students[i], students[maxGradeIndex]);
//        }
//    }
//}
//
//void PrintScholars(Student* students, size_t length, double average)
//{
//    Student newArr[3];
//    int indexOfArr = 0;
//    for (int i = 0; i < length; i++)
//    {
//        if (students[i].averageGrade > average)
//        {
//            newArr[indexOfArr] = students[i];
//            indexOfArr++;
//        }
//    }
//    sortStudents(newArr, indexOfArr);
//    for (int i = 0; i < indexOfArr; i++)
//    {
//        printStudent(newArr[i]);
//    }
//}
//
//int main()
//{
//    Student students[3] ;
//    initStudent(students[0], "Petur", 12346, Course::second, 4.30);
//    initStudent(students[1], "Danail", 67890, Course::first, 5.70);
//    initStudent(students[2], "Mariq", 26642, Course::third, 3.7);
//    PrintScholars(students, 3, 4);
//}

//Task05

//struct Point {
//	int x;
//	int y;
//};
//
//void readPoint(Point& p1)
//{
//	std::cin >> p1.x;
//	std::cin >> p1.y;
//}
//
//void printPoint(const Point& p1)
//{
//	std::cout << "( " << p1.x << ", " << p1.y << " )" << std::endl;
//}
//
//double getDistFromCenter(const Point& p1)
//{
//	return sqrt(p1.x * p1.x + p1.y * p1.y);
//}
//
//double getDistBetweenTwoPoints(const Point& p1, const Point& p2)
//{
//	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
//}
//
//int getQuadrant(const Point& p1)
//{
//	if (p1.x == 0 && p1.y == 0)
//	{
//		std::cout << "This is the center!" << " ";
//		return 0;
//	}
//	if (p1.x > 0 && p1.y > 0)
//	{
//		return 1;
//	}
//	else if (p1.x > 0 && p1.y < 0)
//	{
//		return 4;
//	}
//	else if (p1.x < 0 && p1.y > 0)
//	{
//		return 2;
//	}
//	else
//	{
//		return 3;
//	}
//}
//
//void WhereIsThePoint(const Point& K, int radius)
//{
//	if (getDistFromCenter(K) > radius)
//	{
//		std::cout << "The point is outside the circle!" << std::endl;
//	}
//	else if (getDistFromCenter(K) == radius)
//	{
//		std::cout << "The point is on the circle!" << std::endl;
//	}
//	else
//	{
//		std::cout << "The point is inside the circle!" << std::endl;
//	}
//}
//
//int main()
//{
//	Point p1, p2;
//	readPoint(p1);
//	readPoint(p2);
//	printPoint(p1);
//	printPoint(p2);
//	std::cout << "Distance From Center: " << getDistFromCenter(p1) << std::endl;
//	std::cout << "Distance Between Two Points: " << getDistBetweenTwoPoints(p1, p2) << std::endl;
//	std::cout << "The point is in: " << getQuadrant(p1) << " quadrant!" << std::endl;
//	WhereIsThePoint(p1, 5);
//}

//Task06

enum class Genre{
	Comedy = 0,
	Action = 1,
	Horror = 2,
	Romantic = 3,
	initializator = 4
};

struct Movie
{
	char title[20]{};
	int length = 0;
	Genre genre = Genre::initializator;
	double rating = 0;
};

void createMovie(Movie& movie,const char title[20], int length, Genre genre, double rating)
{
	strcpy_s(movie.title, title);
	movie.length = length;
	movie.genre = genre;
	movie.rating = rating;
}

void funcGenre(char* genre, int key)
{
	switch (key)
	{
	case 0:
		strcpy(genre, "Comedy");
		break;
	case 1:
		strcpy(genre, "Action");
		break;
	case 2:
		strcpy(genre, "Horror");
		break;
	case 3:
		strcpy(genre, "Romantic");
		break;
	default:
		strcpy(genre, "Initializator");
		break;
	}
}

void printMovie(const Movie& movie)
{
	char genre[10]{};
	funcGenre(genre, (int)movie.genre);
	std::cout << "Title: " << movie.title << std::endl;
	std::cout << "Length: " << movie.length << std::endl;
	std::cout << "Genre: " << genre << std::endl;
	std::cout << "Rating: " << movie.rating << std::endl;
}

void printMoviesArr(Movie* movies, int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << "Movie number " << i + 1 << ": " << std::endl;
		printMovie(movies[i]);
		std::cout << std::endl;
	}
}

void printTopMovie(Movie* movies, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		int minRatingIndex = i;
		for (int j = i; j < length; j++)
		{
			if (movies[j].rating < movies[minRatingIndex].rating)
			{
				minRatingIndex = j;
			}
		}
		if (minRatingIndex != i)
		{
			std::swap(movies[i], movies[minRatingIndex]);
		}
	}
	printMovie(movies[length - 1]);
}

int main()
{
	Movie movies[3];
	createMovie(movies[0], "Outer Banks", 135, Genre::Romantic, 9.7);
	createMovie(movies[1], "Shadowhunters", 120, Genre::Action, 3.6);
	createMovie(movies[2], "Hitch", 160, Genre::Comedy, 8.3);
	printMoviesArr(movies, 3);
	std::cout << "The Top Movie Is: " << std::endl;
	printTopMovie(movies, 3);
}