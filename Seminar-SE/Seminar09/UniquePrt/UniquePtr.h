#pragma once

struct A
{
	int x;
	int y;
};

// Pointer which has ownership of
// of type A
class UniquePtr
{
public:
	UniquePtr() = default;
	UniquePtr(A* arg);

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	A& operator*();
	const A& operator*() const;

	A* operator->();
	const A* operator->() const;

	A* get();

	void reset(A* nPtr);
	A* release();

	UniquePtr(UniquePtr&&) noexcept;
	UniquePtr& operator=(UniquePtr&&) noexcept;

	~UniquePtr();
private:
	A* ptr = nullptr;

	void move(UniquePtr&&);
	void free();
};
