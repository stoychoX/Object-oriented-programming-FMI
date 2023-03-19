#include <iostream>
#include <ctime>
const int MAX_EMPLOYEE_NAME = 51;
const int MIN_POS_YEAR = 1900;
const int CURRENT_YEAR = 2023;
const int MIN_PROCENT = 0;
const int MAX_PROCENT = 100;
class Employee {
private:
	char name[MAX_EMPLOYEE_NAME];
	int yearOfAppointment;
	double salary;
	bool isValidName(char* name) {
		return name != nullptr && std::strlen(name) <= MAX_EMPLOYEE_NAME;	
	}
	bool isValidYear(int yearOfAppointment) {
		return yearOfAppointment > MIN_POS_YEAR;
	}
	bool isValidSalary(double salary) {
		return salary > 0;
	}
	int getSalary() {
		return this->salary;
	}
	int getYear() {
		return this->yearOfAppointment;
	}
	char* getName() {
		return this->name;
	}
	void setName(char* name) {
		if (isValidName(name)) {
			strcpy_s(this->name, MAX_EMPLOYEE_NAME, name);
		}
		else {
			strcpy_s(this->name, MAX_EMPLOYEE_NAME, name);
		}
	}
	void setYear(int yearOfAppointment) {
		if (isValidYear(yearOfAppointment)) {
			this->yearOfAppointment = yearOfAppointment;
		}
		else {
			this->yearOfAppointment = MIN_POS_YEAR;
		}
	}
	void setSalary(double salary) {
		if (isValidSalary(salary)) {
			this->salary = salary;
		}
		else {
			this->salary = 0;
		}
	}
public:
	Employee(char* name,int yearOfAppointment, double salary) {
		setName(name);
		setYear(yearOfAppointment);
		setSalary(salary);
	}
	void printEmployee() {
		std::cout << "Name: " << getName() << ", year of appointment: " << getYear()
			<< ", salary: " << getSalary() << std::endl;
	}
	int returnsYearsMadeInCompany() {
		if (CURRENT_YEAR >= getYear()) {
			return CURRENT_YEAR - getYear();
		}
		else {
			return -1;
		}
		
	}
	void increaseSalary(double procent) {
		if (procent >= MIN_PROCENT && procent <= MAX_PROCENT) {
			double newSalary = ((procent/100) * getSalary()) + getSalary();
			setSalary(newSalary);
			return;
		}
		std::cout << "Procent number isn't correct!" << std::endl;
	}
};
int main() {
	char name[7];
	strcpy_s(name, 7, "Atanas");
	Employee employee(name, 2003, 3000);
	employee.printEmployee();
	employee.increaseSalary(50);
	employee.printEmployee();
	
}