#pragma once
#include "EzIO/Value/Value.h"

#include <vector>

namespace EzIO {

class Array : public Value {
public:
	Array() = default;
	Array(std::vector<std::unique_ptr<Value>>&& elements);

	static ValueType getStaticType();

	ValueType getType() const override;
	std::unique_ptr<Value> clone() const override;

	void acceptSerializer(Serializer& serializer) const override;

	size_t getSize() const;
	bool isEmpty() const;
	void clear();

	const std::vector<std::unique_ptr<Value>>& getElements() const;
	std::vector<std::unique_ptr<Value>>& getElements();

	const Value& at(size_t index) const;
	Value& at(size_t index);
	const Value& operator[](size_t index) const;
	Value& operator[](size_t index);
	void setElement(size_t index, std::unique_ptr<Value>&& element);

	void insert(size_t index, std::unique_ptr<Value>&& element);
	void pushBack(std::unique_ptr<Value>&& element);
	void erase(size_t index);
	void popBack();

private:
	void assertNotEmpty() const;
	void assertAccessIndex(size_t index) const;
	void assertInsertIndex(size_t index) const;

	std::vector<std::unique_ptr<Value>> elements;
};

}