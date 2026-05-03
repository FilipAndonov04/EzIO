#pragma once

#include <string>
#include <variant>

#include "EzIO/Value/Array.h"
#include "EzIO/Value/Object.h"

namespace ezio {

class Array;
class Object;

class Value {
public:
	Value() = default;
	template <typename T>
	Value(T&&) = delete;
	Value(double number);
	Value(bool boolean);
	Value(std::string string);
	Value(Array array);
	Value(Object object);
	Value(const Value& other) = default;
	Value(Value& other) = default;
	Value(Value&& other) noexcept = default;
	template <typename T>
	Value& operator=(T&&) = delete;
	Value& operator=(double number);
	Value& operator=(bool boolean);
	Value& operator=(std::string string);
	Value& operator=(Array array);
	Value& operator=(Object object);
	Value& operator=(const Value& other) = default;
	Value& operator=(Value& other) = default;
	Value& operator=(Value&& other) noexcept = default;
	~Value() = default;

	void clear();

	bool isNull() const;
	bool isNumber() const;
	bool isBoolean() const;
	bool isString() const;
	bool isArray() const;
	bool isObject() const;

	double asNumber() const;
	double& asNumber();
	bool asBoolean() const;
	bool& asBoolean();
	const std::string& asString() const;
	std::string& asString();
	const Array& asArray() const;
	Array& asArray();
	const Object& asObject() const;
	Object& asObject();
	
	const double* asNumberPtr() const;
	double* asNumberPtr();
	const bool* asBooleanPtr() const;
	bool* asBooleanPtr();
	const std::string* asStringPtr() const;
	std::string* asStringPtr();
	const Array* asArrayPtr() const;
	Array* asArrayPtr();
	const Object* asObjectPtr() const;
	Object* asObjectPtr();

private:
	void assertConversion(bool isValid, const char* msg) const;

	std::variant<std::monostate, double, bool, std::string, Array, Object> data;
};

}