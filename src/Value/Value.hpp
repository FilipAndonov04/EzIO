#pragma once

#include <string>
#include <variant>

#include "Value/Array.hpp"
#include "Value/Object.hpp"

namespace ezio {

class Value {
public:
	Value() = default;
	Value(const Value&) = default;
	Value(Value&) = default;
	Value(Value&&) noexcept = default;
	template <typename T>
	Value(T&&) = delete;
	Value(double number);
	Value(bool boolean);
	Value(std::string string);
	Value(Array array);
	Value(Object object);
	Value& operator=(const Value&) = default;
	Value& operator=(Value&) = default;
	Value& operator=(Value&&) noexcept = default;
	template <typename T>
	Value& operator=(T&&) = delete;
	Value& operator=(double number);
	Value& operator=(bool boolean);
	Value& operator=(std::string string);
	Value& operator=(Array array);
	Value& operator=(Object object);
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

private:
	std::variant<std::monostate, double, bool, std::string, Array, Object> data;
};

}