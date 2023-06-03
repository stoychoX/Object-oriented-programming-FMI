#include<iostream>
#include"Vector.hpp"
#include"Unique.hpp"
#include"StringView.h"
#include<cstring>
#include<stdexcept>

class Set {
private:
	using element = size_t;

	class SetBase {
	public:

		virtual bool contains(const element&) const = 0;

		virtual SetBase* clone() const = 0;

		virtual ~SetBase() = default;
	};

	class SimpleSet : public SetBase {
	private:
		Vector<element> data;
	public:
		virtual bool contains(const element& arg) const override {
			for (size_t i = 0; i < data.getSize(); i++) {
				if (data[i] == arg) {
					return true;
				}
			}

			return false;
		}

		void insert(const element& arg) {
			if (!contains(arg)) {
				data.pushBack(arg);
			}
		}

		SetBase* clone() const override {
			return new SimpleSet(*this);
		}
	};

	class SetUnion : public SetBase {
	private:
		UniquePointer<SetBase> left;
		UniquePointer<SetBase> right;
	public:
		SetUnion(SetBase* l, SetBase* r) : left(l), right(r) {}

		bool contains(const element& arg) const override {
			return left->contains(arg) || right->contains(arg);
		}

		SetBase* clone() const override {
			return new SetUnion(left->clone(), right->clone());
		}
	};

	class SetIntersection : public SetBase {
	private:
		UniquePointer<SetBase> left;
		UniquePointer<SetBase> right;
	public:
		SetIntersection(SetBase* l, SetBase* r) : left(l), right(r) {}

		bool contains(const element& arg) const override {
			return left->contains(arg) && right->contains(arg);
		}

		SetBase* clone() const override {
			return new SetUnion(left->clone(), right->clone());
		}
	};


	class Parser {
	private:
		static size_t getBalancingIndex(const StringView& str) {
			int balance = 0;

			for (size_t i = 1; i < str.length(); i++) {
				if (str[i] == '{') {
					++balance;
				}
				else if (str[i] == '}') {
					--balance;

					if (balance == 0) {
						return i;
					}
				}
			}
			throw std::runtime_error("Invalid input");
		}

		static size_t getNumber(const StringView& str, size_t& at) {
			size_t toReturn = 0;

			while (std::isdigit(str[at])) {
				toReturn *= 10;
				toReturn += str[at] - '0';

				++at;
			}

			return toReturn;
		}
	public:
		static SetBase* parse(const StringView& str) {
			if (str.length() < 2 || str[0] != '{') {
				throw std::runtime_error("Invalid syntax");
			}
			else if (str.length() == 2) {
				return new SimpleSet;
			}

			if (str[1] == '{') {
				size_t balance = getBalancingIndex(str);

				StringView left = str.substr(1, balance);

				char operation = str[balance + 1];
				StringView right = str.substr(balance + 2, str.length() - balance - 3);

				if (operation == 'v') {
					return new SetUnion(
						parse(left),
						parse(right)
					);
				}
				else if (operation == '^') {
					return new SetIntersection(
						parse(left),
						parse(right)
					);
				}
				else {
					throw std::runtime_error("Invalid input");
				}

			}
			else {
				SimpleSet* toReturn = new SimpleSet;

				element iter = 1;

				while (true) {
					size_t toInsert = getNumber(str, iter);

					toReturn->insert(toInsert);

					if (str[iter] == '}') {
						break;
					}
					iter += 2;
				}

				return toReturn;
			}
		}
	};

	UniquePointer<SetBase> mSet;

	void copyFrom(const Set& other) {
		mSet = other.mSet->clone();
	}
public:
	Set(const MyString& str) : mSet(nullptr) {
		StringView arg(str);

		mSet = Parser::parse(arg);
	}

	bool contains(const element& arg) {
		return mSet->contains(arg);
	}

	Set(const Set& other) : mSet(nullptr) {
		copyFrom(other);
	}

	Set& operator=(const Set& other) {
		if (this != &other) {
			copyFrom(other);
		}

		return *this;
	}
};

int main() {
	MyString input = "{{1, 2, 3}^{3}}";

	Set s(input);

	for (size_t i = 0; i < 10; i++)
	{
		if (s.contains(i)) {
			std::cout << i << " ";
		}
	}
}