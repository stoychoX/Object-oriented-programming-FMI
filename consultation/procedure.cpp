#include<iostream>

template<class T>
class ProcedureBase {
public:
	virtual ProcedureBase<T>* clone() const = 0;
	virtual void execute(T&) const = 0;

	virtual ~ProcedureBase() = default;
};

template<class T, class ProcedureExecutor>
class SimpleProcedure : public ProcedureBase<T> {
protected:
	ProcedureExecutor func;
public:
	SimpleProcedure() = default;

	SimpleProcedure(ProcedureExecutor& p) : func(p) {}

	void execute(T& argument) const override {
		func(argument);
	}

	ProcedureBase<T>* clone() const override {
		return new SimpleProcedure(*this);
	}
};

template<class T>
class CompositeProcedure : public ProcedureBase<T> {
protected:
	ProcedureBase<T>** data;
	size_t size;
	size_t capacity;

	void free() {
		for (size_t i = 0; i < size; i++)
			delete data[i];

		delete[] data;
	}

	void copyFrom(const CompositeProcedure<T>& other) {
		size = other.size;
		capacity = other.capacity;

		data = new ProcedureBase<T>*[capacity] {nullptr};

		for (size_t i = 0; i < size; i++)
			data[i] = other.data[i]->clone();
	}

	void resize(size_t newCapacity) {
		if (newCapacity < size) {
			throw std::exception("Invalid capacity passed");
		}

		ProcedureBase<T>** updatedDatabase = new ProcedureBase<T>*[newCapacity] {nullptr};

		for (size_t i = 0; i < size; i++)
			updatedDatabase[i] = data[i];

		delete[] data;
		data = updatedDatabase;

		capacity = newCapacity;
	}

public:

	CompositeProcedure() : size(0), capacity(8) {
		data = new ProcedureBase<T>*[capacity] {nullptr};
	}

	CompositeProcedure(const CompositeProcedure<T>& other) {
		copyFrom(other);
	}
	CompositeProcedure<T>& operator=(const CompositeProcedure<T>& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}

		return *this;
	}

	void execute(T& argument) const override {
		for (size_t i = 0; i < size; i++)
			data[i]->execute(argument);
	}

	ProcedureBase<T>* clone() const override {
		return new CompositeProcedure<T>(*this);
	}

	void addProcedure(ProcedureBase<T>* arg) {
		if (size == capacity) {
			resize(2 * capacity);
		}

		data[size++] = arg;
	}

	~CompositeProcedure() {
		free();
	}
};

template<class T, T argument>
struct Sum {
	void operator()(T& arg) const {
		arg += argument;
	}
};

template<class T, T argument>
struct Multiply {
	void operator()(T& arg) const {
		arg *= argument;
	}
};

int main() {
	CompositeProcedure<int> root;

	SimpleProcedure<int, Sum<int, 3>>* s = new SimpleProcedure<int, Sum<int, 3>>;
	SimpleProcedure<int, Sum<int, 2>>* s1 = new SimpleProcedure<int, Sum<int, 2>>;
	SimpleProcedure<int, Multiply<int, 3>>* s2 = new SimpleProcedure<int, Multiply<int, 3>>;

	(root).addProcedure(s);
	(root).addProcedure(s1);
	(root).addProcedure(s2);

	int i = 0;

	root.execute(i);
	std::cout << i;
}