//task01
#include<iostream>
#pragma warning (disable: 4996)

unsigned const CURR_YEAR = 2023;
const double MIN_SALARY = 600;

class Employee {
private:
	char name[32];
	unsigned yearOfDeploying;
	double salary = MIN_SALARY;

	void setName(const char* name)
	{
		if (strlen(name) > 32)
		{
			strcpy(this->name, "undefined");
		}
		strcpy(this->name, name);
	}

	void setYear(unsigned year)
	{
		if (year >= 1999)
		{
			this->yearOfDeploying = year;
		}
	}



public:
	Employee(const char* name, unsigned yearOfDeploying)
	{
		setName(name);
		setYear(yearOfDeploying);
	}

	Employee() : Employee("undefined", 0) {}

	unsigned getYearsInServise() const
	{
		unsigned years = CURR_YEAR - this->yearOfDeploying;
		return years;
	}

	void increaseSalaryBy(double percentage)
	{
		if (percentage >= 0 && percentage <= 100)
		{
			this->salary += this->salary * (percentage / 100);
		}
	}

	void introduce() const
	{
		std::cout << "Name: " << this->name << " " << ", Years in work: " << this->getYearsInServise() << ", Salary: " << this->salary << std::endl;
	}
};

int main()
{
	Employee empl1;
	Employee empl2("Gosho", 2005);
	Employee empl3("Ivan", 150);
	empl1.introduce();
	empl2.introduce();
	empl3.introduce();

	empl1.increaseSalaryBy(20);
	empl2.increaseSalaryBy(0);
	empl3.increaseSalaryBy(101);

	empl1.introduce();
	empl2.introduce();
	empl3.introduce();

}

