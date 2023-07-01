/*
* Simple random access iterator implementation.
* 
* Iterator types:
* Output iterator: Can write to the pointed element.
* Input iterator: Can read from the pointed element.
* Forward iterator: Combination of input and output iterator. Can be mover left-to-right [operator++].
* Bidirectional iterator: Forward iterator which can be moved right-to-left[operator--]
* Random access iterator: Bidirectional iterator, which can be moved to a random element
* of the collection in constant time [operator+ and operator-].
*/

#include<iostream>
#include<algorithm>

class RandomAccessIterator {
private:
	int* data;
public:
    using value_type = int;

	RandomAccessIterator(value_type* ptr) : data(ptr) {}

	RandomAccessIterator& operator++() {
		data += 1;
		return *this;
	}

	RandomAccessIterator& operator--() {
		data -= 1;
		return *this;
	}

	RandomAccessIterator operator--(int) {
		RandomAccessIterator copy(*this);
		--(*this);
		return copy;
	}

	RandomAccessIterator operator+(size_t offset) const {
		return RandomAccessIterator(data + offset);
	}

	friend int operator-(const RandomAccessIterator first, const RandomAccessIterator second);

	RandomAccessIterator operator-(size_t offset) const {
		return RandomAccessIterator(data - offset);
	}

	RandomAccessIterator operator++(int) {
		RandomAccessIterator copy(*this);
		++(*this);
		return copy;
	}

	value_type& operator*() const {
		return *data;
	}

	bool operator==(const RandomAccessIterator& other) const {
		return data == other.data;
	}

	bool operator!=(const RandomAccessIterator& other) const {
		return !(*this == other);
	}

	bool operator<(const RandomAccessIterator& other) const {
		return (*data < *other.data);
	}
};

// Used for compatibility with standard library
// when not compiling on MSVC - not mandatory.
template<>
struct std::iterator_traits<RandomAccessIterator> {
    using value_type = int;
    using difference_type = int;
    using iterator_category = std::random_access_iterator_tag;
};

// Used for compatibility with some of the stl's algorithms.
int operator-(const RandomAccessIterator first, const RandomAccessIterator second) {
	return static_cast<int>(second.data - first.data);
}

template<size_t Size>
class SimpleArray {
private:
	int data[Size]{ 0 };
public:

	using Iterator = RandomAccessIterator;

	int operator[](size_t idx) const {
		return data[idx];
	}

	int& operator[](size_t idx) {
		return data[idx];
	}

	Iterator begin() {
		return Iterator(data);
	}

	const Iterator begin() const {
		return Iterator(data);
	}

	const Iterator end() const {
		return Iterator(data);
	}

	size_t length() const {
		return Size;
	}

	Iterator end() {
		return Iterator(data + Size);
	}
};

int main() {
	SimpleArray<10> arr;

	for (size_t i = 0; i < arr.length(); i++)
		arr[i] = i;

	// Range-based for loop
	for (int currentElement : arr) {
		std::cout << currentElement << " ";
	}

	std::cout << std::endl;

	SimpleArray<10>::Iterator result = std::find(arr.begin(), arr.end(), 3);
	std::cout << "After using std::find for 3 we found: " << *result << std::endl;

	std::sort(arr.begin(), arr.end(), [](int lhs, int rhs) {return lhs > rhs; });

	std::cout << "Reverse sort using lambdas, std::sort and iterators: " << std::endl;
	for (int cElement : arr) {
		std::cout << cElement << " ";
	}
	std::cout << std::endl;

	// We can use many more algorithms from standard library...
}