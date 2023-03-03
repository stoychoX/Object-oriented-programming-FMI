#include <iostream>
#include <fstream>

const int STR_SIZE = 32;

void start();

bool contains(const char* str,int start_index, int end_index, char ch) {
	for (int i = start_index; i < end_index; i++) {
		if (str[i] == ch) {
			return true;
		}
	}
	return false;
}

bool isValidPassword(const char* password) {
	bool smallLetterCheck = false, bigLetterCheck = false, numberCheck = false;

	for (int i = 0; i < STR_SIZE; i++) {
		if (!smallLetterCheck && password[i] >= 'a' && password[i] <= 'z') {
			smallLetterCheck = true;
		}
		if (!bigLetterCheck && password[i] >= 'A' && password[i] <= 'Z') {
			bigLetterCheck = true;
		}
		if (!numberCheck && password[i] >= '0' && password[i] <= '9') {
			numberCheck = true;
		}
	}

	if (smallLetterCheck && bigLetterCheck && numberCheck) {
		return true;
	}
	return false;
}

bool isValidUsername(const char* username) {
	for (int i = 0; i < STR_SIZE; i++) {
		if (i != 0 && username[i] == '\0') {
			return true;
		}
		if (username[i] >= '0' && username[i] <= '9') {
			continue;
		}
		if (username[i] >= 'a' && username[i] <= 'z') {
			continue;
		}
		if (username[i] >= 'A' && username[i] <= 'Z') {
			continue;
		}
		if (username[i] != '-' && username[i] != '_' && username[i] != '.') {
			return false;
		}
	}
	return true;
}

bool isValidUser(const char* username, const char* password, const char* email) {
	if (!contains(username, 0, STR_SIZE - 1, '\0')) {
		return false;
	}

	if (!isValidUsername(username)) {
		return false;
	}
	//min symbols for password is 8
	if (contains(password, 0, 8, '\0')) {
		return false;
	}

	if (!contains(password, 0, STR_SIZE - 1, '\0')) {
		return false;
	}

	if (!isValidPassword(password)) {
		return false;
	}

	if (!contains(email, 0, STR_SIZE - 1, '\0')) {
		return false;
	}
}

bool areEqual(const char* str1, const char* str2) {
	int i = 0;
	while (str1[i] && str2[i]) {
		if (str1[i] != str2[i]) {
			return false;
		}
		i++;
	}
	return str1[i] == str2[i];
}

struct user {
	char username[STR_SIZE] = { 0 };
	char password[STR_SIZE] = { 0 };
	char email[STR_SIZE] = { 0 };
};

bool isExistingUser(const user* users,const int userCount,const char* username,const char* email) {
	for (int i = 0; i < userCount; i++) {
		if (areEqual(users[i].username, username)) {
			std::cout << "A user already has that username" << std::endl;
			return true;
		}
		if (areEqual(users[i].email, email)) {
			std::cout << "A user already has that email" << std::endl;
			return true;
		}
	}
	return false;
}

bool createUser(user& r, const char* username, const char* password, const char* email) {
	if (!isValidUser(username, password, email)) {
		return false;
	}

	strcpy_s(r.username, username);
	strcpy_s(r.password, password);
	strcpy_s(r.email, email);
}

void saveUsersToFile(const user* users, const int userCount, const char* filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		return;
	}

	file << userCount << std::endl;

	for (int i = 0; i < userCount; i++) {
		file << users[i].username << std::endl;
		file << users[i].password << std::endl;
		file << users[i].email << std::endl;
	}

	file.close();
}

void addUser(user* users,int& userCount) {
	std::cout << "Please enter username, password and email: " << std::endl;
	char username[STR_SIZE];
	std::cin >> username;
	char password[STR_SIZE];
	std::cin >> password;
	char email[STR_SIZE];
	std::cin >> email;

	if (!isValidUser(username, password, email)) {
		std::cout << "Invalid credentials" << std::endl;
		start();
		return;
	}

	if (isExistingUser(users, userCount, username, email)) {
		start();
		return;
	}

	std::cout << "Successful account creation" << std::endl;

	user u;
	createUser(u, username, password, email);
	users[userCount] = u;
	userCount++;
	saveUsersToFile(users, userCount, "zad5.txt");
}

void login(int& userIndex, const user* users,const int userCount) {
	if (userIndex != -1) {
		std::cout << "Already logged in!" << std::endl;
		return;
	}

	std::cout << "Please enter username and password:" << std::endl;
	char username[STR_SIZE];
	char password[STR_SIZE];
	std::cin >> username;
	std::cin >> password;

	for (int i = 0; i < userCount; i++) {
		if (areEqual(users[i].username, username) && areEqual(users[i].password, password)) {
			std::cout << "Successful login" << std::endl;
			userIndex = i;
			return;
		}
	}

	std::cout << "Incorrect username or password" << std::endl;
}

void changePassword(const int userIndex, user* users) {
	if (userIndex == -1) {
		std::cout << "You need to login first to change your password" << std::endl;
		return;
	}

	std::cout << "Please enter your new password:" << std::endl;
	char newpass[STR_SIZE];
	std::cin >> newpass;
	if (!isValidPassword(newpass)) {
		std::cout << "Invalid password" << std::endl;
		return;
	}
	strcpy_s(users[userIndex].password, newpass);
}

int readUsersFromFile(user* users, const char* filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return 0;
	}

	int userCount = 0;
	file >> userCount;
	file.ignore();

	for (int i = 0; i < userCount; i++) {
		file.getline(users[i].username, STR_SIZE + 1);
		file.getline(users[i].password, STR_SIZE + 1);
		file.getline(users[i].email, STR_SIZE + 1);
	}

	file.close();
	return userCount;
}

void start() {
	user users[100];
	int userCount = readUsersFromFile(users, "zad5.txt");
	int userIndex = -1;
	bool exit = false;

	int key = -1;
	while (!exit) {
		std::cout << "1. Add user" << std::endl;
		std::cout << "2. Login" << std::endl;
		std::cout << "3. Change password" << std::endl;
		std::cout << "4. Exit program" << std::endl;
		std::cin >> key;
		switch (key) {
		case 1: addUser(users, userCount); break;
		case 2: login(userIndex, users, userCount); break;
		case 3: changePassword(userIndex, users); break;
		case 4: exit = true; break;
		}
	}

	saveUsersToFile(users, userCount, "zad5.txt");
	std::exit(0);
}

int main() {
	start();
}