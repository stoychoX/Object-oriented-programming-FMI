#include "Bitset.h"
#include<algorithm>

size_t Bitset::getBucketCount() const {
    return (maxNumbers + 1) / 8 + 1;
}

size_t Bitset::getMask(size_t number) const {
    size_t mask = 1;
    
    size_t shift = number % 8;
    
    mask = (mask << (7 - shift));

    return mask;
}

size_t Bitset::getBucket(size_t number) const {
    return number / 8;
}

Bitset::Bitset(size_t maxNum) : maxNumbers{maxNum} {
    size_t bucketCount = getBucketCount();

    data = new unsigned char[bucketCount] {};
}

Bitset::Bitset(const Bitset& other) {
    copyFrom(other);
}

Bitset& Bitset::operator=(const Bitset& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

void Bitset::addNumber(size_t number) {
    if (number > maxNumbers) {
        // Ако случайно искаме да добавяме произволно големи числа:
        
        // Bitset toCopy(number);

        // for (size_t i = 0; i < getBucketCount(); i++)
        //     toCopy.data[i] = data[i];

        // operator=(toCopy);
        // addNumber(number);
        return;
    }

    size_t bucketIdx = getBucket(number);
    size_t mask = getMask(number);

    data[bucketIdx] = (data[bucketIdx] | mask);
}

bool Bitset::contains(size_t number) const {
    if (number > maxNumbers)
        return false;

    size_t bucketIdx = getBucket(number);
    size_t mask = getMask(number);

    return ((data[bucketIdx] & mask) != 0);
}

void Bitset::removeNumber(size_t number) {
    if (number > maxNumbers)
        return;

    size_t bucketIdx = getBucket(number);
    size_t mask = getMask(number);

    data[bucketIdx] = (data[bucketIdx] & (~mask));
}

Bitset Bitset::unionBitset(const Bitset& other) const {
    size_t maxCapacity = std::max(maxNumbers, other.maxNumbers);
    size_t minCapacity = std::min(maxNumbers, other.maxNumbers);

    size_t maxRange = std::max(getBucketCount(), other.getBucketCount());
    size_t minRange = std::min(getBucketCount(), other.getBucketCount());

    const Bitset& bigger = (maxNumbers > other.maxNumbers) ? *this : other;

    Bitset toReturn(maxCapacity);

    for (size_t i = 0; i < minRange; i++)
        toReturn.data[i] = (data[i] | other.data[i]);

    for (size_t i = minRange; i < maxRange; i++)
        toReturn.data[i] = bigger.data[i];

    return toReturn;
}

Bitset Bitset::intersectBitset(const Bitset& other) const {
    size_t minCapacity = std::min(maxNumbers, other.maxNumbers);
    
    size_t minRange = std::min(getBucketCount(), other.getBucketCount());

    Bitset toReturn(minCapacity);

    for (size_t i = 0; i < minRange; i++)
        toReturn.data[i] = (data[i] & other.data[i]);

    return toReturn;
}

Bitset Bitset::compliment() const {
    Bitset toReturn(*this);

    for (size_t i = 0; i < toReturn.getBucketCount(); i++)
        toReturn.data[i] = ~toReturn.data[i];

    return toReturn;
}

size_t Bitset::getMaxNumber() const {
    return maxNumbers;
}

Bitset::~Bitset() {
    free();
}

void Bitset::free() {
    delete[] data;
}

void Bitset::copyFrom(const Bitset& other) {
    size_t bucketCount = other.getBucketCount();
    data = new unsigned char[bucketCount] {};

    for (size_t i = 0; i < bucketCount; i++)
        data[i] = other.data[i];

    maxNumbers = other.maxNumbers;
}
