#include <iostream>
#pragma warning(disable: 4996)

class Employee {
	char name[50];
	int year;
	int salary;
public:
	Employee(const char* name,const int year,const int salary) {
		strcpy(this->name, name);
		this->year = year;
		this->salary = salary;
	}
	Employee() : Employee("", 0, 0) {}

	char* getName() {
		return name;
	}
	int getYear() {
		return year;
	}
	int getSalary() {
		return salary;
	}

	void setName(const char* name) {
		strcpy(this->name, name);
	}
	void setYear(const int year) {
		this->year = year;
	}
	void setSalary(const int salary) {
		this->salary = salary;
	}

	void increaseSalary(const double percent) {
		salary *= 1 + percent / 100;
	}
};

int main() {
	Employee e("Ivan",5,2000);

	std::cout << e.getName() << std::endl;
	std::cout << e.getYear() << std::endl;
	std::cout << e.getSalary() << std::endl;

	e.setName("Petur");
	e.setYear(10);
	e.setSalary(3000);
	
	std::cout << e.getName() << std::endl;
	std::cout << e.getYear() << std::endl;
	std::cout << e.getSalary() << std::endl;

	e.increaseSalary(50);
	std::cout << e.getSalary() << std::endl;
}