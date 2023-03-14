#include <iostream>
#include <stdlib.h>
#pragma warning(disable: 4996)

struct User {
	char name[32];
	char password[32];
	char email[32];
};

enum CheckBy {
	name,
	email
};

const size_t MAX_COUNT_USERS = 100;
size_t countLoggedUsers = 0;
User* users = new User[MAX_COUNT_USERS];
User admin{ "sd","12345678Aa","admin@gmail.com" };
User loggedUser = admin;

bool VerifyPassword(char* pass)
{
	size_t indexPass = 0;
	bool hasCapitalLetter = false;
	bool hasLowerLetter = false;
	bool hasDigit = false;
	while (pass[indexPass] != '\0')
	{
		char symbol = pass[indexPass++];
		if (!hasCapitalLetter)
		{
			hasCapitalLetter = (symbol >= 'A' && symbol <= 'Z');
		}
		if (!hasLowerLetter)
		{
			hasLowerLetter = (symbol >= 'a' && symbol <= 'z');
		}
		if (!hasDigit)
		{
			hasDigit = (symbol >= '0' && symbol <= '9');
		}
	}
	return (hasCapitalLetter && hasLowerLetter && hasDigit && (indexPass >= 8));
}

bool CheckUniqueByCriteria(CheckBy criteria, User newUser, User* users, size_t countLoggedUsers)
{
	switch (criteria)
	{
	case name:
		for (size_t i = 0; i < countLoggedUsers; i++)
		{
			if (strcmp(users[i].name, newUser.name) == 0)
			{
				return false;
			}
		}
		break;
	case email:
		for (size_t i = 0; i < countLoggedUsers; i++)
		{
			if (strcmp(users[i].email, newUser.email) == 0)
			{
				return false;
			}
		}
		break;
	default:
		return false;
	}
	return true;
}

User ReadUser()
{
	User user;
	std::cout << "Enter name: ";
	std::cin.getline(user.name, 32);
	std::cout << "Enter password: ";
	std::cin.getline(user.password, 32);
	std::cout << "Enter email: ";
	std::cin.getline(user.email, 32);
	return user;
}

bool VerifyUser(User user)
{
	if (!VerifyPassword(user.password))
	{
		std::cout << "Your password is incorrect!" << std::endl;
		std::cout << "It must contain letter from \'A-Z\' and \'a-z\' and digit from \'1-9\' and have length >= 8!" << std::endl;
		return false;
	}
	if (!CheckUniqueByCriteria(CheckBy::name, user, users, countLoggedUsers))
	{
		std::cout << "There is already user with name " << user.name << "!" << std::endl;
		return false;
	}
	if (!CheckUniqueByCriteria(CheckBy::email, user, users, countLoggedUsers))
	{
		std::cout << "There is already user with email " << user.email << "!" << std::endl;
		return false;
	}
	return true;
}

bool AddNewUser(User user)
{
	if (VerifyUser(user))
	{
		users[countLoggedUsers++] = user;
		return true;
	}
	return false;
}

User& GetUserByName(char* name)
{
	for (size_t i = 0; i < countLoggedUsers; i++)
	{
		if (strcmp(users[i].name, name) == 0)
		{
			return users[i];
		}
	}
}

int GetIdUserByName(char* name)
{
	for (size_t i = 0; i < countLoggedUsers; i++)
	{
		if (strcmp(users[i].name, name)==0)
		{
			return i;
		}
	}
	return -1;
}

bool LogIn(char* name, char* pass)
{
	User user;
	strcpy(user.name, name);
	if (!CheckUniqueByCriteria(CheckBy::name, user, users, countLoggedUsers))
	{
		User user = GetUserByName(name);
		if ((strcmp(user.password, pass) == 0))
		{
			loggedUser = user;
			return true;
		}
	}
	return false;
}

void PrintMainMenu()
{
	std::cout << "   Menu" << std::endl;
	std::cout << "1. Login" << std::endl;
	std::cout << "2. Add new user" << std::endl;
	std::cout << "3. Exit" << std::endl;
	std::cout << "Choose index: ";
}

void PrintMenuLoggedUser()
{
	std::cout << "    Menu" << std::endl;
	std::cout << "1. Change password" << std::endl;
	std::cout << "2. Log out" << std::endl;
	std::cout << "Choose index: ";
}

bool ChangePassword(char* newPass)
{
	if (VerifyPassword(newPass))
	{
		int idUser = GetIdUserByName(loggedUser.name);
		strcpy(users[idUser].password, newPass);
		return true;
	}
	return false;
}

void StartUp();
void ManageLoggedUser()
{
	while (true)
	{
		PrintMenuLoggedUser();
		int indexChosen;
		std::cin >> indexChosen;
		std::cin.ignore();
		switch (indexChosen)
		{
		case 1:
			system("CLS");
			std::cout << "Enter new password: ";
			char newPass[32];
			std::cin >> newPass;
			if (ChangePassword(newPass))
			{
				system("CLS");
				std::cout << "Successfully changed!" << std::endl;
			}
			else
			{
				std::cout << "Invalid password!" << std::endl;
			}
			break;
		case 2:
			system("CLS");
			loggedUser = admin;
			StartUp();
			return;
		default:
			system("CLS");
			std::cout << "Wrong index!" << std::endl;
			break;
		}
	}
}

User GetLoginData()
{
	system("CLS");
	User user;
	std::cout << "Name: ";
	std::cin >> user.name;
	std::cout << "Password: ";
	std::cin >> user.password;
	return user;
}

void StartUp()
{
	while (true)
	{
		PrintMainMenu();
		int indexChosen;
		std::cin >> indexChosen;
		std::cin.ignore();
		switch (indexChosen)
		{
		case 1:
			User userToLog = GetLoginData();
			system("CLS");
			if (LogIn(userToLog.name, userToLog.password))
			{
				std::cout << "Successfully logged!" << std::endl;
				ManageLoggedUser();
				return;
			}
			else
			{
				std::cout << "No that user in the system!" << std::endl;
			}
			break;
		case 2:
			system("CLS");
			User newUser = ReadUser();
			system("CLS");
			if (AddNewUser(newUser))
			{
				std::cout << "Successfully added!" << std::endl;
			}
			break;
		case 3:
			system("CLS");
			std::cout << "Goodbye";
			return;
		default:
			system("CLS");
			std::cout << "Wrong index!" << std::endl;
			break;
		}
	}
}

int main()
{
	StartUp();
}

