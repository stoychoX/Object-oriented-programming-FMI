#include <iostream>
#include <fstream>
const int MAX_COUNT_PAIRS = 25;
const int MAX_SIZE_FILENAME = 100;
enum class errors {
	errorToOpenOfs = -2,
	errorToOpenIfs
};
struct pair {
	size_t x;
	size_t y;
};
struct relation {
	pair pairs[MAX_COUNT_PAIRS];
	int currCountPairs = 0;
};
pair createPair(int x, int y) {
	pair myNewPair = {0, 0};
	if (x >= 0 && y >= 0) {
		myNewPair.x = x;
		myNewPair.y = y;
	}
	return myNewPair;
}
void initPair(pair& toInit, int x, int y) {
	if (x >= 0 && y >= 0) {
		toInit.x = x;
		toInit.y = y;
		return;
	}
	toInit = { 0, 0 };
}
pair readPairFromFile(std::ifstream& ifs) {
	pair newPair = {0, 0};
	int x, y;
	int last_x = 0, last_y = 0;
	while (ifs >> x >> y) {
		last_x = x;
		last_y = y;
	}
	if (last_x >= 0 && last_y >= 0) {
		newPair.x = last_x;
		newPair.y = last_y;
	}
	return newPair;
}
void writePairToFile(std::ofstream& ofs,
	const pair& toWrite) {
	ofs << toWrite.x << " " << toWrite.y;
	ofs << std::endl;
}
void printPairToConsole(const pair& myPair) {
	std::cout << myPair.x << " " << myPair.y;
	std::cout << std::endl;
}
bool addPair(relation& arg, const pair& toInsert) {
	if (arg.currCountPairs < 25) {
		arg.pairs[arg.currCountPairs] = toInsert;
		++arg.currCountPairs;
		return true;
	}
	else {
		return false;
	}
}
bool writeRelation(std::ofstream& ofs, const relation& arg) {
	if (!ofs.is_open()) {
		return false;
	}
	for (int i = 0; i < arg.currCountPairs; i++) {
		writePairToFile(ofs, arg.pairs[i]);
	}
	return true;
}
bool arePairsEqual(const pair& one, const pair& two) {
	return one.x == two.x && one.y == two.y;
}
bool readRelation(std::ifstream& ifs, relation& arg) {
	if (!ifs.is_open()) return false;
	pair myPair = readPairFromFile(ifs);
	for (int i = 0; i < arg.currCountPairs; i++) {
		if (!arePairsEqual(myPair, arg.pairs[i])) {
			addPair(arg, myPair);
		}
	}
	return true;
}
int main() {
	int x, y;
	std::cin >> x >> y;
	std::ofstream write("task.txt", std::ios::app);
	if (!write.is_open()) {
		std::cout << "Error to open write_stream" << std::endl;
		return (int)errors::errorToOpenOfs;
	}
	pair myPair = createPair(x, y);
	relation rel;
	std::cout << "Pair added to relation: ";
	std::cout << addPair(rel, myPair) << std::endl;
	std::cout << "Relation saved to file: ";
	std::cout << writeRelation(write, rel) << std::endl;
	write.close();
	std::ifstream read("task.txt");
	if (!read.is_open()) {
		std::cout << "Error to open read_stream" << std::endl;
		return (int)errors::errorToOpenIfs;
	}
	myPair = readPairFromFile(read);
	std::cout << "Relation read: " <<
		readRelation(read, rel) << std::endl;
	printPairToConsole(myPair);
	read.close();
}