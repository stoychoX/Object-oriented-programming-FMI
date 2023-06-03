#pragma once
#include<exception>
#include"Vector.hpp"
#include"StringView.h"
#include"Unique.hpp"

class Set {
private:
	class SetBase {
	public:

		virtual bool contains(size_t) const = 0;

		virtual SetBase* clone() const = 0;

		virtual ~SetBase() = default;
	};

	class SimpleSet : public SetBase {
	private:
		Vector<size_t> data;
	public:
		bool contains(size_t arg) const override {
            for (size_t i = 0; i < data.getSize(); i++) {
                if (data[i] == arg) {
                    return true;
                }
            }

            return false;
        }


		void insert(size_t arg) {
            if(!contains(arg)) {
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

		bool contains(size_t arg) const override {
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

		bool contains(size_t arg) const override {
			return left->contains(arg) && right->contains(arg);
		}

		SetBase* clone() const override {
			return new SetUnion(left->clone(), right->clone());
		}
	};

	class Parser {
	private:
		static size_t findLeftExpressionEnd(const StringView& str) {
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

        static bool isDigit(char c) {
            return c>= '0' && c <= '9';
        }

		static size_t getNumber(const StringView& str, size_t& at) {
			size_t toReturn = 0;

			while (isDigit(str[at])) {
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
			else if (str.length() == 2 && str[1] == '}') {  // Empty set corner case hardcode
				return new SimpleSet;
			}

			if (str[1] == '{') {
				size_t leftExprEnd = findLeftExpressionEnd(str);

				StringView left = str.substr(1, leftExprEnd);

				char operation = str[leftExprEnd + 1];

				StringView right = str.substr(leftExprEnd + 2, str.length() - leftExprEnd - 3);

				if (operation == 'v') {
					return new SetUnion
                    (
						parse(left),
						parse(right)
					);
				}
				else if (operation == '^') {
					return new SetIntersection
                    (
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

				size_t currentPosition = 1;

				while (true) {
					size_t toInsert = getNumber(str, currentPosition);

					toReturn->insert(toInsert);

					if (str[currentPosition] == '}') {
						break;
					}
					currentPosition += 2;
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

	bool contains(const size_t& arg) {
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
