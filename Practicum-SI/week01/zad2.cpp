#include <iostream>

int printBiggerAscii(const int* arr, const int N, const char ch) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		if (arr[i] > ch) {
			count++;
		}
	}
	return count;
}

int main() {
	int N;
	std::cin >> N;

	int* arr = new int[N];
	for (int i = 0; i < N; i++) {
		std::cin >> arr[i];
	}

	char ch;
	std::cin >> ch;

	std::cout << printBiggerAscii(arr, N, ch);
	delete[] arr;
}