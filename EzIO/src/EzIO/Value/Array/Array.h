#pragma once
#include "EzIO/Value/Value.h"

#include <vector>

namespace EzIO {

class Value;

class Array {
public:
	Array() = default;
	Array(size_t initialCapacity);

	size_t getSize() const;
	bool isEmpty() const;
	void clear();

	const Value& operator[](size_t index) const;
	Value& operator[](size_t index);

	void pushBack(const Value& value);
	void pushBack(Value&& value);
	void insert(size_t index, const Value& value);
	void insert(size_t index, Value&& value);
	void popBack();
	void erase(size_t index);

	std::vector<Value>::const_iterator cbegin() const;
	std::vector<Value>::const_iterator cend() const;
	std::vector<Value>::const_iterator begin() const;
	std::vector<Value>::const_iterator end() const;
	std::vector<Value>::iterator begin();
	std::vector<Value>::iterator end();

private:
	void assertNotEmpty() const;
	void assertAccessIndex(size_t index) const;
	void assertInsertIndex(size_t index) const;

	std::vector<Value> values;
};

}