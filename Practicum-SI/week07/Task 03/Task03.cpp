#include <iostream>
#include "Group.h"

int main()
{
	Student a("Ivan", 1234, 4.56);
	Student b("Toncho", 67899, 5.66);
	Student students[2]{ a,b };

	Group gr(students, 2);
	gr.safeToBinary("Students.txt");
	gr.getGroupFromBinary("Students.txt");

	gr.print();
    gr.addStudent({"Pesho", 13579, 5.77});
	gr.print();
}
