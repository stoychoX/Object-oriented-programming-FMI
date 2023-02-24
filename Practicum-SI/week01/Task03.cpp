#include <iostream>
const int MAX_SIZE = 100;
struct OrderedPair {
	int first = 0;
	int second = 0;
};
void readOrderedPair(OrderedPair& pair) {
	std::cin >> pair.first;
	std::cin >> pair.second;
}
void printOrderedPair(const OrderedPair pair) {
	std::cout << "(" << pair.first
		<< ", " << pair.second 
		<< ")";
	std::cout << std::endl;
}
void readArrOfPairs(OrderedPair * pairs, int len) {
	for (int i = 0; i < len; i++) {
		readOrderedPair(pairs[i]);
	}
}
bool isLargerPair(const OrderedPair pair1, 
	const OrderedPair pair2) {
	return (pair1.first > pair2.first ||
		(pair1.first == pair2.first &&
			pair1.second > pair2.second));
}

OrderedPair maxOrderedPair(const OrderedPair * pairs) {
	OrderedPair maxPair = pairs[0];
	for (int i = 1; i < MAX_SIZE; i++) {
		if (isLargerPair(pairs[i], maxPair)) {
			maxPair = pairs[i];
		}
	}
	return maxPair;
}
void sortOrderedPairsArr(OrderedPair * arr, const int len) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (isLargerPair(arr[j], arr[j + 1])) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}