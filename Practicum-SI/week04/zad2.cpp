#include <iostream>
#pragma warning(disable: 4996)

class Task {
	char task[256];
	char password[9];
	int loginFails;
	int points;

	bool isCorrectPassword(const char* password) {
		return strcmp(this->password, password) == 0;
	}

public:
	Task(const char* task, const char* password, const int points) {
		strcpy(this->task, task);
		strcpy(this->password, password);
		this->loginFails = 0;
		this->points = points;
	}
	Task() : Task("", "", 0) {}

	char* getTask(const char* password) {
		if (isCorrectPassword(password)) {
			return task;
		}
		else {
			loginFails++;
			return nullptr;
		}
	}

	void setPassword(const char* newPassword, const char* oldPassword) {
		if (isCorrectPassword(oldPassword)) {
			strcpy(this->password, newPassword);
		}
	}

	char* getPassword() {
		return password;
	}

	void setTask(const char* task, const char* password) {
		if (isCorrectPassword(password)) {
			strcpy(this->task, task);
		}
	}

	int getLoginFails() {
		return loginFails;
	}

	void setEqual(Task t) {
		strcpy(task, t.getTask(t.getPassword()));
		strcpy(password, t.getPassword());
		loginFails = t.getLoginFails();
		points = t.points;
	}
};



int main() {
	Task t("Create hex viewer program", "123456", 50);
	char* task = t.getTask("asdf");
	if (task != nullptr) // is nullptr
		std::cout << task << std::endl;

	task = t.getTask("123456");
	if (task != nullptr) // isn't nullptr
		std::cout << task << std::endl;

	t.setPassword("654321", "123456");
	t.setTask("Invert binary tree", "123456"); //wrong password

	task = t.getTask("654321");
	if (task != nullptr) // isn't nullptr
		std::cout << task << std::endl;

	t.setTask("Invert binary tree", "654321"); // successful

	task = t.getTask("654321");
	if (task != nullptr) // isn't nullptr
		std::cout << task << std::endl;

	std::cout << t.getLoginFails() << std::endl;
}