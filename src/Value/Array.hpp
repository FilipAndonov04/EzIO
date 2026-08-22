#pragma once

#include <vector>

namespace ezio {

class Value;

class Array {
public:
	using Iterator = std::vector<Value>::iterator;
	using ConstIterator = std::vector<Value>::const_iterator;

public:
	Array() = default;
	Array(size_t initialCapacity);

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;

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

private:
	void assertNotEmpty() const;
	void assertAccessIndex(size_t index) const;
	void assertInsertIndex(size_t index) const;

private:
	std::vector<Value> values;
};

}