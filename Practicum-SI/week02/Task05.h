#pragma once
#include <iostream>
#include <sstream>
const short MAX_COUNT_USERS = 100;
const short MAX_LEN_NAME = 32;
const short MAX_LEN_PASS = 32;
const short MAX_LEN_EMAIL = 32;
const short MIN_PASS_LEN = 8;
const char* FILE_NAME = "users.txt";

struct User {
	char name[MAX_LEN_NAME];
	char password[MAX_LEN_PASS];
	char email[MAX_LEN_EMAIL];
};

struct SystemUsers {
	User users[MAX_COUNT_USERS];
	short count = 0;
};

bool IsLowLetter(const char& symbol) 
{
	return (symbol >= 97 && symbol <= 122);
}

bool IsHighLetter(const char& symbol) 
{
	return (symbol >= 65 && symbol <= 90);
}

bool IsDigit(const char& number) 
{
	return number >= 48 && number <= 57;
}

bool IsNameValid(const char name[])
{
	short index = 0;
	while (name[index] != '\0')
	{
		if (!IsHighLetter(name[index]) && !IsLowLetter(name[index]) &&
			!IsDigit(name[index]) && name[index] != '-' && name[index] != '_' &&
			name[index] != '.')
		{
			return false;
		}
		index++;

	}

	return true;
}

bool IsPassValid(const char pass[])
{
	short countHighLetters = 0;
	short countLowLetters = 0;
	short countDigits = 0;
	short index = 0;
	while (pass[index] != '\0')
	{
		if (IsDigit(pass[index])) countDigits++;
		else if (IsHighLetter(pass[index])) countHighLetters++;
		else if (IsLowLetter(pass[index])) countLowLetters++;

		index++;
	}

	return countDigits > 0 && countHighLetters > 0 && 
		   countLowLetters > 0 && index >= 8;
}

void WriteUserToFile(std::ofstream& fileOut, const User& user)
{
	fileOut << user.name << ',' << user.password << ',' << user.email << "\n";
}

void CreateUserFromConsole(User& user)
{
	std::cout << "Type name: ";
	std::cin >> user.name;
	std::cout << std::endl;
	std::cout << "Type password: ";
	std::cin >> user.password;
	std::cout << "Type email: ";
	std::cin >> user.email;
}

bool AreStringsEqual(const char* string1, const char* string2)
{
	short index = 0;
	while (string1[index] != '\0' || string2[index] != '\0')
	{
		if (string1[index] != string2[index])
		{
			return false;
		}
		index++;
	}

	return true;
}

bool IsNameUnique(const SystemUsers& systemUsers, const char name[])
{
	for (size_t i = 0; i < systemUsers.count; i++)
	{
		if (AreStringsEqual(systemUsers.users[i].name, name)) 
		{
			return false;
		}
	}

	return true;
}

bool IsEmailUnique(const SystemUsers& systemUsers, const char email[])
{
	for (size_t i = 0; i < systemUsers.count; i++)
	{
		if (AreStringsEqual(systemUsers.users[i].email, email))
		{
			return false;
		}
	}

	return true;
}

bool RegisterUser(const char* fileOutName, SystemUsers system)
{
	std::ofstream fileOut(fileOutName, std::ios::app);
	if (!fileOut.is_open())
	{
		std::cout << "File not open!";
		return false;
	}

	User newUser;
	CreateUserFromConsole(newUser);
	if (!IsPassValid(newUser.password) || !IsNameValid(newUser.name))
	{
		std::cout << "Incorrect user data!";
		return false;
	}

	if (!IsEmailUnique(system, newUser.email))
	{
		std::cout << "Not unique email!";
		return false;
	}

	if (!IsNameUnique(system, newUser.name))
	{
		std::cout << "Not unique name!";
		return false;
	}

	WriteUserToFile(fileOut, newUser);
	fileOut.close();

	system.users[system.count++] = newUser;
	return true;
}

void GetLogInUserData(User& user)
{
	std::cin.ignore();
	std::cout << "Name: ";
	std::cin.getline(user.name, MAX_LEN_NAME);
	std::cout << std::endl;
	std::cout << "Password: ";
	std::cin.getline(user.password, MAX_LEN_NAME);
	std::cout << std::endl;
}

int LogInUser(const SystemUsers& system)
{
	User user;
	GetLogInUserData(user);

	for (size_t i = 0; i < system.count; i++)
	{
		if (AreStringsEqual(user.name, system.users[i].name)) 
		{
			if (AreStringsEqual(user.password, system.users[i].password))
			{
				std::cout << "User logged in!\n";
				return i;
			}
			else
			{
				std::cout << "False password!\n";
				return -1;
			}
		}
	}

	std::cout << "Not existing username!";
	return false;
}

bool OverwriteFileUsers(const char* fileOutName, SystemUsers system)
{
	std::ofstream fileOut(fileOutName);
	if (!fileOut.is_open())
	{
		std::cout << "File not open!";
		return false;
	}

	for (size_t i = 0; i < system.count; i++)
	{
		WriteUserToFile(fileOut, system.users[i]);
	}

	fileOut.close();
	return true;
}

bool ChangePassword(User& user)
{
	char password[MAX_LEN_PASS];
	std::cin.ignore();
	std::cout << "Type your new passoword: ";
	std::cin.getline(password, MAX_LEN_PASS);

	if (AreStringsEqual(user.password, password))
	{
		std::cout << "The password is the same!\n";
		return false;
	}

	if (!IsPassValid(password))
	{
		std::cout << "Invalid password!\n";
		return false;
	}
	
	std::stringstream passBuffer;
	passBuffer << password;
	passBuffer >> user.password;

	std::cout << "Password changed!\n";
	return true;
}

void LoadUserFromFile(std::ifstream& fileIn, User& user)
{
	fileIn.getline(user.name, MAX_LEN_NAME, ',');
	fileIn.getline(user.password, MAX_LEN_PASS, ',');
	fileIn.getline(user.email, MAX_LEN_EMAIL);
}

size_t GetLinesFile(std::ifstream& fileIn)
{
	size_t count = 0;
	while (true)
	{
		char buffer[1024];
		fileIn.getline(buffer, 1024);
		if (fileIn.eof())
		{
			break;
		}
		count++;
	}

	fileIn.clear();
	fileIn.seekg(0, std::ios::beg);

	return count;
}

size_t LoadUsers(const char* fileInName, SystemUsers& systemUsers)
{
	std::ifstream fileIn(fileInName);
	if (!fileIn.is_open())
	{
		std::cout << "File didn't open!";
		return -1;
	}
	size_t countUsers = GetLinesFile(fileIn);

	for (size_t i = 0; i < countUsers; i++)
	{
		LoadUserFromFile(fileIn, systemUsers.users[i]);
		systemUsers.count++;
	}

	fileIn.close();
	return countUsers;
}

void ExecuteTask5()
{
	SystemUsers systemUsers;
	char action = '\0';
	std::cout << "Type R for register.\nType L for login\nAction: ";
	std::cin >> action;
	LoadUsers(FILE_NAME, systemUsers);
	if (action == 'L')
	{
		int indexUser = LogInUser(systemUsers);
		if (indexUser == -1) 
		{
			return;
		}
		
		std::cout << "Do you want to change your password? Y or N: ";
		std::cin >> action;	
		if (action == 'Y')
		{
			ChangePassword(systemUsers.users[indexUser]);
			OverwriteFileUsers(FILE_NAME, systemUsers);
		}
		
	}
	else if (action == 'R')
	{	
		RegisterUser(FILE_NAME, systemUsers);
	}
}