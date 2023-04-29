#pragma once
#include<cstddef> //size_t

class StringPool {
private:
	class LittleString {
	private:
		char data[64]{};
	public:
		LittleString();

		LittleString(const char*);

		const char* getString() const;

		bool operator==(const LittleString&) const;

		bool operator<(const LittleString& other) const;

		size_t refCount = 0;

	};

	LittleString** data{ nullptr };
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const StringPool&);

	void resize(size_t nCap);
public:
	StringPool(size_t cap);

	StringPool(const StringPool&);
	StringPool& operator=(const StringPool&);

	size_t mSize() const;

	void remove(size_t idx);
	void remove(const LittleString&);

	bool contains(const LittleString&) const;

	bool empty() const;

	void insert(const LittleString&);

	int find(const LittleString&) const;

	const LittleString& operator[](size_t) const;

	~StringPool();
};
