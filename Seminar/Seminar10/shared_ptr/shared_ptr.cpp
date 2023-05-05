#include "shared_ptr.h"

void shared_ptr::reference_counter::free() {
	if (value() < 1)
		delete count;
}

void shared_ptr::reference_counter::copyFrom(const reference_counter& other) {
	count = other.count;
	increment();
}

shared_ptr::reference_counter::reference_counter() {
	count = new int;
	*count = 0;
}

shared_ptr::reference_counter::reference_counter(const reference_counter& other) {
	copyFrom(other);
}

shared_ptr::reference_counter& shared_ptr::reference_counter::operator=(const reference_counter& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

void shared_ptr::reference_counter::increment() {
	assert(count != nullptr);
	++(*count);
}

void shared_ptr::reference_counter::decrement() {
	assert(count != nullptr);
	--(*count);
}

int shared_ptr::reference_counter::value() const {
	assert(count != nullptr);
	return *count;
}

shared_ptr::reference_counter::~reference_counter() {
	free();
}

void shared_ptr::free() {
	if (rc.value() == 1) {
		delete ptr;
	}

	rc.decrement();
}

void shared_ptr::copyFrom(const shared_ptr& other) {
	ptr = other.ptr;
	rc = other.rc;
}

shared_ptr::shared_ptr() {
	ptr = nullptr;
	rc.increment();
}

shared_ptr::shared_ptr(int* mPtr) {
	ptr = mPtr;
	rc.increment();
}

void shared_ptr::reset() {
	*this = shared_ptr();
}

shared_ptr::shared_ptr(const shared_ptr& other) {
	copyFrom(other);
}

bool shared_ptr::unique() const {
	return (rc.value() == 1);
}

bool shared_ptr::operator!() const {
	return (ptr == nullptr);
}

int shared_ptr::operator*() const {
	return *ptr;
}

int& shared_ptr::operator*() {
	return *ptr;
}

size_t shared_ptr::use_count() const {
	return rc.value();
}

shared_ptr& shared_ptr::operator=(const shared_ptr& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

shared_ptr::~shared_ptr() {
	free();
}
