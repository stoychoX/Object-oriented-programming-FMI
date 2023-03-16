#include <iostream>

const int NAME_LENGTH = 51;
const size_t CURRENT_YEAR = 2023;

class Employee
{
	char _name[NAME_LENGTH];
	size_t _hireYear;
	double _salary;

public:
	Employee(const char* name, size_t hireYear, double salary)
	{
		setName(name);
		setHireYear(hireYear);
		setSalary(salary);
	}


	const char* getName() const
	{
		return _name;
	}

	const size_t getHireYear() const
	{
		return _hireYear;
	}

	const double getSalary() const
	{
		return _salary;
	}


	size_t experienceInCurrentCompanyInYears() const
	{
		return CURRENT_YEAR - _hireYear;
	}


	void increaseSalary(double percent)
	{
		if (percent < 0)
			return;

		_salary += _salary * percent / 100.0;
	}


private:
	void setName(const char* name)
	{
		strcpy_s(_name, NAME_LENGTH, name);
	}

	void setHireYear(size_t hireYear)
	{
		_hireYear = hireYear > CURRENT_YEAR ? CURRENT_YEAR : hireYear;
	}

	void setSalary(double salary)
	{
		_salary = salary < 0 ? 0 : salary;
	}
};

int main()
{
}
