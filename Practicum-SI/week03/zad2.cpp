#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

struct Offer {
	char companyName[25];
	unsigned employeeCount;
	unsigned payedDayOffCount;
	unsigned pay;
};

void inputOfferFromConsole(Offer& o) {
	char tempname[25];
	unsigned temp;
	std::cout << "Company name:" << std::endl;
	std::cin >> tempname;
	strcpy(o.companyName, tempname);
	std::cout << "Employee count:" << std::endl;
	std::cin >> temp;
	o.employeeCount = temp;
	std::cout << "Payed Day off count:" << std::endl;
	std::cin >> temp;
	o.payedDayOffCount = temp;
	std::cout << "Pay:" << std::endl;
	std::cin >> temp;
	o.pay = temp;
}

void writeOfferToFile(const Offer& o, std::ofstream& os) {
	os << o.companyName << std::endl;
	os << o.employeeCount << std::endl;
	os << o.payedDayOffCount << std::endl;
	os << o.pay << std::endl;
}

void inputConsoleToFile(const char* fileName) {
	int n;
	std::cin >> n;
	std::ofstream os(fileName, std::ios::out | std::ios::app);
	if (!os.is_open()) {
		return;
	}

	for (int i = 0; i < n; i++) {
		Offer o;
		inputOfferFromConsole(o);
		writeOfferToFile(o,os);
	}
}

bool readOfferFromFile(Offer& o, std::ifstream& is) {
	char temp = is.get();
	if (is.eof() || temp == '\n') {
		return false;
	}
	is.seekg(-1, std::ios::cur);

	char tempname[25];
	is.getline(tempname, 25);
	strcpy(o.companyName, tempname);
	is >> o.employeeCount;
	is.ignore();
	is >> o.payedDayOffCount;
	is.ignore();
	is >> o.pay;
	is.ignore();
	return true;

}

void printOffer(const Offer& o) {
	std::cout << "Company Name: " << o.companyName << std::endl;
	std::cout << "Employee count: " << o.employeeCount << std::endl;
	std::cout << "Payed day off count: " << o.payedDayOffCount << std::endl;
	std::cout << "Pay: " << o.pay << std::endl;
}

void filterOffer(const char* filePath, size_t minSalary) {
	std::ifstream is(filePath);
	if (!is.is_open()) {
		return;
	}
	Offer o;
	while (readOfferFromFile(o, is)) {
		if (o.pay > minSalary) {
			printOffer(o);
		}
	}
}

bool findOffer(const char* filePath, const char* name) {
	std::ifstream is(filePath);
	if (!is.is_open()) {
		return false;
	}

	Offer o;
	while (readOfferFromFile(o, is)) {
		if (strcmp(o.companyName, name) == 0) {
			return true;
		}
	}
	return false;
}

int main() {
	//inputConsoleToFile("filezad2.txt");
	filterOffer("filezad2.txt", 2000);
	std::cout << std::endl << std::boolalpha << findOffer("filezad2.txt", "??????") << std::endl;
}