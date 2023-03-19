#include <iostream>
#include <ctime>
namespace EmployeeConsts {
	const int MAX_EMPLOYEE_NAME = 51;
	const int MIN_POS_YEAR = 1900;
	const int CURRENT_YEAR = 2023;
	const int MIN_PROCENT = 0;
	const int MAX_PROCENT = 100;
}
class Employee {
private:
	char name[EmployeeConsts::MAX_EMPLOYEE_NAME];
	int yearOfAppointment;
	double salary;
	bool isValidName(char* name) {
		return name != nullptr && std::strlen(name) <= EmployeeConsts::MAX_EMPLOYEE_NAME;
	}
	bool isValidYear(int yearOfAppointment) {
		return yearOfAppointment > EmployeeConsts::MIN_POS_YEAR;
	}
	bool isValidSalary(double salary) {
		return salary > 0;
	}
	int getSalary() const {
		return this->salary;
	}
	int getYear() const {
		return this->yearOfAppointment;
	}
	const char* getName() const {
		return this->name;
	}
	void setName(char* name) {
		if (isValidName(name)) {
			strcpy_s(this->name, EmployeeConsts::MAX_EMPLOYEE_NAME, name);
		}
		else {
			strcpy_s(this->name, EmployeeConsts::MAX_EMPLOYEE_NAME, "");
		}
	}
	void setYear(int yearOfAppointment) {
		if (isValidYear(yearOfAppointment)) {
			this->yearOfAppointment = yearOfAppointment;
		}
		else {
			this->yearOfAppointment = EmployeeConsts::MIN_POS_YEAR;
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
	void printEmployee() const {
		std::cout << "Name: " << getName() << ", year of appointment: " << getYear()
			<< ", salary: " << getSalary() << std::endl;
	}
	int returnsYearsMadeInCompany() {
		if (EmployeeConsts::CURRENT_YEAR >= getYear()) {
			return EmployeeConsts::CURRENT_YEAR - getYear();
		}
		else {
			return -1;
		}
		
	}
	void increaseSalary(double procent) {
		if (procent >= EmployeeConsts::MIN_PROCENT && procent <= EmployeeConsts::MAX_PROCENT) {
			double newSalary = ((procent/100) * getSalary()) + getSalary();
			setSalary(newSalary);
			return;
		}
		std::cout << "Procent number isn't correct!" << std::endl;
	}
};
namespace TaskConsts {
	const int MAX_LEN_TASK_NAME = 257;
	const int LEN_PASSWORD = 10;
}
class Task {
private:
	char taskCondition[TaskConsts::MAX_LEN_TASK_NAME];
	char password[TaskConsts::LEN_PASSWORD];
	int countFailedLogins;
	int points;
	bool isValidTaskCon(const char* taskCondition) const {
		return taskCondition != nullptr &&
			std::strlen(taskCondition) < TaskConsts::MAX_LEN_TASK_NAME;
	}
	bool isValidPassword(const char* password) const {
		return password != nullptr &&
			std::strlen(password) == TaskConsts::LEN_PASSWORD - 1;
	}
	bool isValidPoints(int points) const {
		return points > 0;
	}
public:
	Task(char* taskCondition, char* password, int points) {
		this->countFailedLogins = 0;
		if (isValidTaskCon(taskCondition) &&
			isValidPassword(password) &&
			isValidPoints(points)) {
			strcpy_s(this->taskCondition, TaskConsts::MAX_LEN_TASK_NAME, taskCondition);
			strcpy_s(this->password, TaskConsts::LEN_PASSWORD, password);
			this->points = points;
		}
		else {
			strcpy_s(this->taskCondition, TaskConsts::MAX_LEN_TASK_NAME, "");
			strcpy_s(this->password, TaskConsts::LEN_PASSWORD, "");
			this->points = 0;
		}
	}
};
int main() {
	
}