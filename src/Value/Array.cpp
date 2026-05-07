#include "EzIO/Value/Array.h"

#include <stdexcept>

#include "EzIO/Value/Value.h"

namespace ezio {

Array::Array(size_t initialCapacity) {
    values.reserve(initialCapacity);
}

size_t Array::getSize() const {
	return values.size();
}

bool Array::isEmpty() const {
	return values.empty();
}

void Array::clear() {
    values.clear();
}

const Value& Array::operator[](size_t index) const {
	assertAccessIndex(index);
    return values[index];
}

Value& Array::operator[](size_t index) {
    assertAccessIndex(index);
    return values[index];
}

void Array::pushBack(const Value& value) {
    values.push_back(value);
}

void Array::pushBack(Value&& value) {
    values.push_back(std::move(value));
}

void Array::insert(size_t index, const Value& value) {
    assertInsertIndex(index);
    values.insert(values.begin() + index, value);
}

void Array::insert(size_t index, Value&& value) {
    assertInsertIndex(index);
    values.insert(values.begin() + index, std::move(value));
}

void Array::popBack() {
    assertNotEmpty();
    values.pop_back();
}

void Array::erase(size_t index) {
    assertAccessIndex(index);
    values.erase(values.begin() + index);
}

Array::ConstIterator Array::cbegin() const {
    return values.cbegin();
}

Array::ConstIterator Array::cend() const {
    return values.cend();
}

Array::ConstIterator Array::begin() const {
    return values.begin();
}

Array::ConstIterator Array::end() const {
    return values.end();
}

Array::Iterator Array::begin() {
    return values.begin();
}

Array::Iterator Array::end() {
    return values.end();
}

void Array::assertNotEmpty() const {
    if (isEmpty()) {
        throw std::out_of_range("empty array");
    }
}

void Array::assertAccessIndex(size_t index) const {
    if (index >= getSize()) {
        throw std::out_of_range("insert index out of bound");
    }
}

void Array::assertInsertIndex(size_t index) const {
    if (index > getSize()) {
        throw std::out_of_range("access index out of bound");
    }
}

}