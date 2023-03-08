#include <iostream>
#include <fstream>
enum class ErrorStatusIOF {
	failedToOpen = -1,
	allGood
};
int countOfChExcTwoChars(std::ifstream& ifs,
	char first, char sec) {
	if (!ifs.is_open()) {
		return (int)ErrorStatusIOF::failedToOpen;
	}
	char ch;
	int counter = 0;
	while (true) {
		ch = ifs.get();
		//EOF char is not counted!!!
		if (ifs.eof()) {
			break;
		}
		if (ch != first && ch != sec) {
			++counter;
		}
	}
	return counter;
}
int main() {
	std::ifstream readingStream("myFile.txt");
	std::cout << countOfChExcTwoChars(readingStream, 'a', 'd');
      readingStream.close();
}