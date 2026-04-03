#pragma once

#include <string>

namespace EzIO {

class Value;
class Array;
class Object;

class Serializer {
public:
	virtual void serialize(const Value& value) = 0;
	virtual void serialize(double number) = 0;
	virtual void serialize(bool boolean) = 0;
	virtual void serialize(const std::string& string) = 0;
	virtual void serialize(const Array& array) = 0;
	virtual void serialize(const Object& object) = 0;
};

}