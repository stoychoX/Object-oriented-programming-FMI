#include <iostream>
#include <fstream>

namespace pairs {
	struct pair {
		int x;
		int y;
	};

	pair createPair(int x, int y) {
		pair p = { x,y };
		return p;
	}

	void initPair(pair& toInit, int x, int y) {
		toInit = { x,y };
	}

	pair readPairFromFile(std::ifstream& inFile) {
		int x, y;
		inFile >> x >> y;
		pair p = { x, y };
		return p;
	}

	void writePairToFile(std::ofstream& outFile, const pair& toWrite) {
		outFile << (toWrite.x) << " " << (toWrite.y) << std::endl;
	}
}

namespace relations {
	using namespace pairs;
	const int maxRelationCount = 25;

	struct relation {
		pair pairs[maxRelationCount];
		int currentRelationCount = 0;
	};

	bool addPair(relation& arg, pair& toInsert) {
		if (arg.currentRelationCount == maxRelationCount) {
			return false;
		}
		arg.currentRelationCount++;
		arg.pairs[arg.currentRelationCount - 1] = toInsert;
		return true;
	}

	bool writeRelation(const relation& arg, const char* filePath) {
		std::ofstream output(filePath);
		if (!output.is_open()) {
			return false;
		}

		output << arg.currentRelationCount << " ";

		for (int i = 0; i < arg.currentRelationCount; i++) {
			output << arg.pairs[i].x << " " << arg.pairs[i].y << " ";
		}
		return true;
	}

	bool readRelation(relation& arg, const char* filepath) {
		std::ifstream input(filepath);
		if (!input.is_open()) {
			return false;
		}

		int relationCount;
		input >> relationCount;
		arg.currentRelationCount = relationCount;

		for (int i = 0; i < relationCount; i++) {
			int x, y;
			input >> x >> y;
			arg.pairs[i] = {x , y};
		}

		return true;
	}
}

int main() {
	using namespace pairs;
	using namespace relations;

	relation r;
	pair p;

	p = createPair(2, 3);
	addPair(r, p);
	p = createPair(10, 2);
	addPair(r, p);
	p = createPair(-5, 6);
	addPair(r, p);
	p = createPair(0, 0);
	addPair(r, p);
	p = createPair(1, 9);
	addPair(r, p);

	writeRelation(r, "zad3.txt");

	relation r1;
	readRelation(r1, "zad3.txt");

	for (int i = 0; i < r1.currentRelationCount; i++) {
		std::cout << r1.pairs[i].x << " " << r1.pairs[i].y << std::endl;
	}
}