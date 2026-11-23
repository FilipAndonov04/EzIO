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

	void clear() noexcept;

	bool isNull() const noexcept;
	bool isNumber() const noexcept;
	bool isBoolean() const noexcept;
	bool isString() const noexcept;
	bool isArray() const noexcept;
	bool isObject() const noexcept;

	const double* asNumber() const noexcept;
	double* asNumber() noexcept;
	const bool* asBoolean() const noexcept;
	bool* asBoolean() noexcept;
	const std::string* asString() const noexcept;
	std::string* asString() noexcept;
	const Array* asArray() const noexcept;
	Array* asArray() noexcept;
	const Object* asObject() const noexcept;
	Object* asObject() noexcept;

	double asNumberOrDefault() const noexcept;
	bool asBooleanOrDefault() const noexcept;
	const std::string& asStringOrDefault() const noexcept;
	const Array& asArrayOrDefault() const noexcept;
	const Object& asObjectOrDefault() const noexcept;

private:
	std::variant<std::monostate, double, bool, std::string, Array, Object> data;
};

}