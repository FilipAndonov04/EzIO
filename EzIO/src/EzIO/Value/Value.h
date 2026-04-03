#pragma once

#include <string>

namespace EzIO {

class Array;
class Object;

class Value {
public:
	Value() = default;
	Value(double number);
	Value(bool boolean);
	Value(std::string string);
	Value(Array array);
	Value(Object object);
	Value(const Value& other);
	Value(Value&& other) noexcept;
	Value& operator=(double number);
	Value& operator=(bool boolean);
	Value& operator=(std::string string);
	Value& operator=(Array array);
	Value& operator=(Object object);
	Value& operator=(const Value& other);
	Value& operator=(Value&& other) noexcept;
	~Value();

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

	void clear();

private:
	void assertConversion(bool isValid, const char* msg) const;
	void copyFrom(const Value& other);
	void moveFrom(Value&& other) noexcept;

	double* number = nullptr;
	bool* boolean = nullptr;
	std::string* string = nullptr;
	Array* array = nullptr;
	Object* object = nullptr;
};

}