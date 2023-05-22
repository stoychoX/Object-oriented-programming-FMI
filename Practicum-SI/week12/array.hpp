#pragma once
template<typename T, size_t len>
class array {
public:
	size_t size() const;
	void fill(int);
	T& operator[](size_t i);
	bool empty() const;

private:
	T arr[len];
};
template<typename T, size_t len>
size_t array<T, len>::size() const {
	return len;
}
template<typename T, size_t len>
void  array<T, len>::fill(int x) {
	for (int i = 0; i < len; i++) {
		arr[i] = x;
	}
}
template<typename T, size_t len>
T& array<T, len>::operator[](size_t i) {
	return arr[i];
}
template<typename T, size_t len>
bool array<T, len>::empty() const {
	return len == 0;
}