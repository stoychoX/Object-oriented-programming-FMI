#include <iostream>
#include <fstream>

struct logtime {
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
};

struct Log {
	char name[16] = {0};
	unsigned int ipv4 = 0;
	logtime logtime;
};

bool writeLog(const Log& toWrite, std::ofstream& outFile) {
	outFile << toWrite.name << "," << toWrite.ipv4 << "," << toWrite.logtime.hours;
	outFile <<  "," << toWrite.logtime.minutes << "," << toWrite.logtime.seconds << std::endl;
	return true;
}

bool writeLogs(Log* logs, size_t size, const char* filePath) {
	std::ofstream outFile(filePath);
	if (!outFile.is_open()) {
		return false;
	}

	for (size_t i = 0; i < size; i++) {
		writeLog(logs[i], outFile);
	}
	outFile.close();
	return true;
}

bool readLog(Log& toRead, std::ifstream& inFile) {
	inFile.get();
	if (inFile.eof()) {
		return false;
	}
	inFile.seekg(-1, std::ios::cur);

	char name[16];
	inFile.getline(name, 20, ',');
	strcpy_s(toRead.name, name);

	inFile >> toRead.ipv4;
	inFile.ignore();
	inFile >> toRead.logtime.hours;
	inFile.ignore();
	inFile >> toRead.logtime.minutes;
	inFile.ignore();
	inFile >> toRead.logtime.seconds;
	inFile.ignore();
	return true;
}

size_t logsCount(const char* filePath) {
	std::ifstream is(filePath);
	if (!is.is_open()) {
		return -1;
	}

	size_t count = 0;
	while (true) {
		char ch = is.get();
		if (is.eof()) {
			break;
		}
		if (ch == '\n') {
			count++;
		}
	}
	is.close();

	return count;
}

size_t readLogs(Log* logs, const char* filePath) {
	std::ifstream is(filePath);
	if (!is.is_open()) {
		return 0;
	}

	size_t size = 0;
	while (true) {
		Log l;
		if (!readLog(l, is)) {
			break;
		}
		logs[size] = l;
		size++;
	}
	return size;
}

int main() {
	std::ofstream os("zad4.txt");
	if (!os.is_open()) {
		return -1;
	}

	Log l[3] = { { "ivan",1, {2, 3, 4} } ,
				 { "petar",2, {20, 30, 40} },
				 { "samuil",3, {00, 30, 59} } 
	};

	writeLogs(l, 3, "zad4.txt");

	Log logs[5] = {0};
	size_t size = readLogs(logs, "zad4.txt");
	for (size_t i = 0; i < size; i++) {
		std::cout << "Name: " << logs[i].name << std::endl;
		std::cout << "ipv4: " << logs[i].ipv4 << std::endl;
		std::cout << "logtime: " << logs[i].logtime.hours << ":" << logs[i].logtime.minutes << ":" << logs[i].logtime.seconds << std::endl;
	}
}