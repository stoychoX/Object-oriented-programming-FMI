#include <iostream>

struct OrderedPair {
	int first;
	int second;
};

void readOrderedPair(OrderedPair& op) {
	std::cin >> op.first;
	std::cin >> op.second;
}

bool isBigger(const OrderedPair& op1,const OrderedPair& op2) {
	return ((op1.first > op2.first) || ((op1.first == op2.first) && (op1.second > op2.second)));
}

OrderedPair biggestOrderedPair(const OrderedPair arr[100]) {
	int indexOfBiggest = 0;
	for (int i = 1; i < 100; i++) {
		if (isBigger(arr[i], arr[indexOfBiggest])) {
			indexOfBiggest = i;
		}
	}
	return arr[indexOfBiggest];
}

void swapOrderedPairs(OrderedPair& op1, OrderedPair& op2){
	int temp = op1.first;
	op1.first = op2.first;
	op2.first = temp;

	temp = op1.second;
	op1.second = op2.second;
	op2.second = temp;
}

void sortOrderedPairArray(OrderedPair* arr, int len) {
	for (int i = 0; i < len - 1; i++) {
		int min = i;
		for (int j = i + 1; j < len; j++) {
			if (isBigger(arr[min], arr[j])) {
				min = j;
			}
		}
		swapOrderedPairs(arr[i], arr[min]);
	}
}