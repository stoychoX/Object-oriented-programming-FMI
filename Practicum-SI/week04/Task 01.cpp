#include <iostream>

const int CURRENT_YEAR = 2023;

class Employee
{
private:
    char _name[50];
    int _yearOfEmployment;
    double _salary;

    bool isLetter(char a)
    {
        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
        {
            return true;
        }
        else return false;
    }

    bool isValidString(const char* a)
    {
        int length = strlen(a);
        for (int i = 0; i < length; i++)
        {
            if (!isLetter(a[i]))
            {
                return false;
            }
        }
        return true;
    }
public:

    const char* getName() const
    {
        return _name;
    }

    int getYearOfEmployment() const
    {
        return _yearOfEmployment;
    }

    double getSalary() const
    {
        return _salary;
    }

    void setName(const char* name)
    {
        if(isValidString(name))
        {
            strcpy(_name, name);
        }
        else
        {
            return;
        }
    }

    void setYearofEmployment(int a)
    {
        _yearOfEmployment = a;
    }

    void setSalary(double salary)
    {
        _salary = abs(salary);
    }

    Employee(const char* name, int yearOfEmployment, int salary)
    {
        setName(name);
        setYearofEmployment(yearOfEmployment);
        setSalary(salary);
    }

    Employee() :Employee("default", 0, 0) {}

    int yearsInCompany()
    {
        return CURRENT_YEAR - _yearOfEmployment;
    }

    void raiseSalary(double percent)
    {
        _salary += _salary * (percent / 100);
    }
};

int main()
{
  
}