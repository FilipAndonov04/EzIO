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
	explicit Array(size_t initialCapacity) { values.reserve(initialCapacity); }

	Iterator begin() noexcept { return values.begin(); }
	Iterator end() noexcept { return values.end(); }
	ConstIterator begin() const noexcept { return values.begin(); }
	ConstIterator end() const noexcept { return values.end(); }
	ConstIterator cbegin() const noexcept { return values.cbegin(); }
	ConstIterator cend() const noexcept { return values.cend(); }

	size_t size() const noexcept { return values.size(); }
	bool isEmpty() const noexcept { return values.empty(); }

	void clear() noexcept { values.clear(); }

	const Value& operator[](size_t index) const;
	Value& operator[](size_t index);

	void pushBack(const Value& value);
	void pushBack(Value&& value);
	void insert(size_t index, const Value& value);
	void insert(size_t index, Value&& value);
	void popBack();
	void erase(size_t index);

private:
	std::vector<Value> values;
};

}