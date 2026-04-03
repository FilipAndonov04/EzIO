#include "Array.h"
#include "EzIO/IO/Serializer/Serializer.h"
#include "EzIO/IO/Deserializer/Deserializer.h"
#include "EzIO/Exception/Value/ValueException.h"

namespace EzIO {

Array::Array(std::vector<std::unique_ptr<Value>>&& elements) 
    : elements(std::move(elements)) {}

ValueType Array::getStaticType() {
    return ValueType::Array;
}

ValueType Array::getType() const {
    return getStaticType();
}

std::unique_ptr<Value> Array::clone() const {
    std::vector<std::unique_ptr<Value>> copies;
    copies.reserve(elements.size());

    for (const auto& element : elements) {
        copies.push_back(element->clone());
    }

    return std::make_unique<Array>(std::move(copies));
}

void Array::acceptSerializer(Serializer& serializer) const {
    serializer.serialize(*this);
}

size_t Array::getSize() const {
    return elements.size();
}

bool Array::isEmpty() const {
    return getSize() == 0;
}

void Array::clear() {
    elements.clear();
}

const std::vector<std::unique_ptr<Value>>& Array::getElements() const {
    return elements;
}

std::vector<std::unique_ptr<Value>>& Array::getElements() {
    return elements;
}

const Value& Array::at(size_t index) const {
    assertAccessIndex(index);

    return *elements[index];
}

Value& Array::at(size_t index) {
    assertAccessIndex(index);

    return *elements[index];
}

const Value& Array::operator[](size_t index) const {
    return at(index);
}

Value& Array::operator[](size_t index) {
    return at(index);
}

void Array::setElement(size_t index, std::unique_ptr<Value>&& element) {
    assertAccessIndex(index);

    elements[index] = std::move(element);
}

void Array::insert(size_t index, std::unique_ptr<Value>&& element) {
    assertInsertIndex(index);

    elements.insert(elements.begin() + index, std::move(element));
}

void Array::pushBack(std::unique_ptr<Value>&& element) {
    elements.push_back(std::move(element));
}

void Array::erase(size_t index) {
    assertAccessIndex(index);

    elements.erase(elements.begin() + index);
}

void Array::popBack() {
    assertNotEmpty();

    elements.pop_back();
}

void Array::assertNotEmpty() const {
    if (isEmpty()) {
        throw ValueException("empty array");
    }
}

void Array::assertAccessIndex(size_t index) const {
    if (index >= getSize()) {
        throw ValueException("insert index out of bound");
    }
}

void Array::assertInsertIndex(size_t index) const {
    if (index > getSize()) {
        throw ValueException("access index out of bound");
    }
}

}