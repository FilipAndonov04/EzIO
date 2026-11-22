#pragma once

#include <ios>

namespace ezio {

class Value;
class Array;
class Object;

class JsonSerializer {
public:
	JsonSerializer(std::ostream& outputStream);

	void serialize(const Value& value);
	void serialize(double number);
	void serialize(bool boolean);
	void serialize(const std::string& string);
	void serialize(const Array& array);
	void serialize(const Object& object);

	void setOutputStream(std::ostream& outputStream);

private:
	void startNewLine();

private:
	std::ostream* outputStream;
	unsigned tabs = 0;
};

}