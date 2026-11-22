#include "Value/Array.hpp"

#include "Value/Value.hpp"
#include "Verify.hpp"

namespace ezio {

const Value& Array::operator[](size_t index) const {
	verify(index < size(), "index out of bound");
	return values[index];
}

Value& Array::operator[](size_t index) {
	verify(index < size(), "index out of bound");
	return values[index];
}

void Array::pushBack(const Value& value) {
	values.push_back(value);
}

void Array::pushBack(Value&& value) {
	values.push_back(std::move(value));
}

void Array::insert(size_t index, const Value& value) {
	verify(index <= size(), "index out of bound");
	values.insert(values.begin() + index, value);
}

void Array::insert(size_t index, Value&& value) {
	verify(index <= size(), "index out of bound");
	values.insert(values.begin() + index, std::move(value));
}

void Array::popBack() {
	verify(!isEmpty(), "empty array");
	values.pop_back();
}

void Array::erase(size_t index) {
	verify(index < size(), "index out of bound");
	values.erase(values.begin() + index);
}

}