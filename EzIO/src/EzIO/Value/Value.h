#pragma once
#include "EzIO/Value/ValueType.h"

#include <memory>

namespace EzIO {

class Serializer;
class Deserializer;

class Value {
public:
	Value() = default;
	Value(const Value&) = delete;
	Value& operator=(const Value&) = delete;
	virtual ~Value() = default;

	virtual ValueType getType() const = 0;
	virtual std::unique_ptr<Value> clone() const = 0;

	virtual void acceptSerializer(Serializer& serializer) const = 0;
};

}