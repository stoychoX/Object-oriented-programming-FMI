#pragma once
#include<cassert>

class shared_ptr {
private:
	class reference_counter {
	private:
		int* count = nullptr;

		void free();
		void copyFrom(const reference_counter&);
	public:
		reference_counter();
		
		reference_counter(const reference_counter&);
		reference_counter& operator=(const reference_counter&);

		void increment();
		void decrement();

		int value() const;

		~reference_counter();
	};

	int* ptr = nullptr;
	reference_counter rc;

	void free();
	void copyFrom(const shared_ptr&);
public:
	shared_ptr();
	shared_ptr(int* mPtr);

	void reset();

	shared_ptr(const shared_ptr&);

	int operator*() const;

	bool unique() const;

	bool operator!() const;

	int& operator*();

	size_t use_count() const;

	shared_ptr& operator=(const shared_ptr&);

	~shared_ptr();
};

