#include "StringPool.h"
#include<cstring>	// strcmp etc.
#include<stdexcept> // std::runtime_error
#include<cassert>   // assert

StringPool::LittleString::LittleString() {
	data[0] = '\0';
}

StringPool::LittleString::LittleString(const char* arg) {
	if (strlen(arg) < 64) {
		strcpy_s(data, arg);
	}
}

const char* StringPool::LittleString::getString() const {
	return data;
}

bool StringPool::LittleString::operator==(const LittleString& other) const {
	return (strcmp(data, other.data) == 0);
}

bool StringPool::LittleString::operator<(const LittleString& other) const {
	return (strcmp(data, other.data) == -1);
}

void StringPool::free() {
	for (size_t i = 0; i < size; i++) {
		if (data[i]->refCount == 1)
			delete data[i];
		else
			data[i]->refCount--;
	}
	delete[] data;
}

void StringPool::copyFrom(const StringPool& other) {
	size = other.size;
	capacity = other.capacity;

	data = new LittleString * [other.capacity] {nullptr};
	
	assert(size < other.capacity);

	for (size_t i = 0; i < size; i++) {
		data[i] = other.data[i];
		other.data[i]->refCount++;
	}
}

void StringPool::resize(size_t nCap) {
	LittleString** nData = new LittleString * [nCap] {nullptr};

	assert(size < nCap);

	for (size_t i = 0; i < size; i++) {
		nData[i] = data[i];
		data[i] = nullptr;
	}

	delete[] data;
	data = nData;

	capacity = nCap;
}

StringPool::StringPool(size_t cap) {
	size = 0;
	capacity = cap;

	data = new LittleString * [cap] {nullptr};
}

StringPool::StringPool(const StringPool& other) {
	copyFrom(other);
}

StringPool& StringPool::operator=(const StringPool& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

size_t StringPool::mSize() const {
	return size;
}

void StringPool::remove(size_t idx) {
	if (idx >= size) {
		throw std::runtime_error("Invalid index!");
	}

	LittleString* cArg = data[idx];

	for (size_t i = idx; i < size-1; i++) {
		data[i] = data[i + 1];
	}

	if (cArg->refCount == 1) {
		delete cArg;
	}
	else {
		cArg->refCount--;
	}

	data[size - 1] = nullptr;
	size--;
}

void StringPool::remove(const LittleString& arg) {
	int cIndx = find(arg);

	if (cIndx == -1) {
		throw std::runtime_error("Element doesn't exist in collection");
	}

	remove(cIndx);
}

bool StringPool::contains(const LittleString& arg) const {
	return (find(arg) != -1);
}

bool StringPool::empty() const {
	return (size == 0);
}

void StringPool::insert(const LittleString& arg) {
	if (size == capacity) {
		resize(capacity * 2);
	}

	size_t indexAt = size;

	while (indexAt != 0 && data[indexAt - 1] != nullptr && (arg < *data[indexAt - 1])) {
		data[indexAt] = data[indexAt - 1];
		indexAt--;
	}

	if (indexAt != 0 && data[indexAt - 1] != nullptr && (arg == *data[indexAt - 1])) {
		data[indexAt] = data[indexAt - 1];
		data[indexAt]->refCount++;
	}
	else {
		data[indexAt] = new LittleString(arg);
		data[indexAt]->refCount = 1;
	}

	size++;
}

int StringPool::find(const LittleString& arg) const {
	int l = 0;
	int r = size - 1;

	int at = -1;

	while (l <= r) {
		int mid = l + (r - l) / 2;

		if (*data[mid] < arg) {
			l = mid + 1;
		}
		else {
			if (*data[mid] == arg)
				at = mid;

			r = mid - 1;
		}
	}

	return at;
}

const StringPool::LittleString& StringPool::operator[](size_t idx) const {
	if (idx >= size)
		throw std::runtime_error("Invalid index");

	return *data[idx];
}

StringPool::~StringPool() {
	free();
}