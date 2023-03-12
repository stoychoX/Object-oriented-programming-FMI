#include <iostream>

int min(const int a,const int b) {
	return (a < b) ? a : b;
}
int minReference(const int& a,const int& b) {
	return (a < b) ? a : b;
}
int minPointer(const int* a, const int* b) {
	return ((*a) < (*b)) ? (*a) : (*b);
}

int main() {
	int a, b;
	std::cin >> a;
	std::cin >> b;
	std::cout << min(a, b) << " ; " << minReference(a, b) << " ; " << minPointer(&a, &b);
}