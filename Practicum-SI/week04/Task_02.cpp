//task02
#include <iostream>
#pragma warning (disable : 4996)

class Task {
private:
	char description[256];
	char password[9];
	unsigned countInvalidEnters = 0;
	double pointsCount = 0.0;

	void setDesc(const char* desc)
	{
		if (!strlen(desc) > 256)
		{
			strcpy(this->description, desc);
		}
	}
	void setPass(const char* pass)
	{
		int a = strlen(pass);
		if (!(strlen(pass) > 9))
		{
			strcpy(this->password, pass);
		}
	}
public:
	Task(const char* desc, const char* pass)
	{
		setDesc(desc);
		setPass(pass);
	}

	Task() : Task("undefined", "") {}


	bool login(const char* password) const
	{
		return (strcmp(this->password, password) == 0);
	}

	bool setPassword(const char* newPasswd, const char* oldPasswd)
	{
		if (login(oldPasswd))
		{//we should return if the set was correct so the setpass should be bool
			setPass(newPasswd);
			return true;
		}
		return false;
	}

	bool setTask(const char* task, const char* passwd)
	{
		if (login(passwd))
		{
			setDesc(task);
			return true;
		}
		return false;
	}

	const char* getTask(const char* passwd)
	{
		if (login(passwd))
		{
			return this->description;
		}
		this->countInvalidEnters++;
		return nullptr;
	}

	unsigned getLoginFails() const
	{
		return this->countInvalidEnters;
	}

};

int main()
{
	Task task1("task01", "123456");
	Task task2("task02", "abcd");
	std::cout << "Enter pass: ";
	char passUser[10];
	std::cin >> passUser;
	std::cout << (task1.setPassword("newPass", passUser) ? "Yes" : "No");
	std::cout << std::endl;
	std::cin >> passUser;
	std::cout << (task1.setPassword("newPass", passUser) ? "Yes" : "No");
	std::cout << std::endl;
}