#include"unique_ptr.h"
#include<utility> // std::move
unique_pointer::unique_pointer(int* mem) {
    mPointer = mem;
}

void unique_pointer::moveFrom(unique_pointer&& other) {
    mPointer = other.mPointer;
    other.mPointer = nullptr;
}

unique_pointer::unique_pointer(unique_pointer&& other) {
    moveFrom(std::move(other));
}

unique_pointer& unique_pointer::operator=(unique_pointer&& other) {
    if(this != &other) {
        destroy();
        moveFrom(std::move(other));
    }

    return *this;
}

bool unique_pointer::operator!() const {
    return (mPointer == nullptr);
}

int& unique_pointer::operator*() {
    return *mPointer;
}

int unique_pointer::operator*() const {
    return *mPointer;
}

unique_pointer::operator bool() const {
    return mPointer != nullptr;
}

void unique_pointer::destroy() {
    delete mPointer;
}

unique_pointer::~unique_pointer() {
    destroy();
}