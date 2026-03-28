#pragma once
#include "Json/Value/ValueType.h"

namespace Json {

class Value {
public:
	Value() = default;
	Value(const Value&) = delete;
	Value& operator=(const Value&) = delete;
	virtual ~Value() = default;

	virtual ValueType getType() const = 0;
};

}