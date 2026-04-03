#pragma once

namespace EzIO {

class Value;
class Number;
class String;
class Boolean;
class Array;
class Object;
class Null;

class Serializer {
public:
	virtual void serialize(const Value& value) = 0;
	virtual void serialize(const Number& number) = 0;
	virtual void serialize(const String& string) = 0;
	virtual void serialize(const Boolean& boolean) = 0;
	virtual void serialize(const Array& array) = 0;
	virtual void serialize(const Object& object) = 0;
	virtual void serialize(const Null& null) = 0;
};

}