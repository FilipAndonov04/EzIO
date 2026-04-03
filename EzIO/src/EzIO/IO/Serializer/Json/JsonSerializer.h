#pragma once
#include "EzIO/IO/Serializer/Serializer.h"

#include <ios>

namespace EzIO {

class JsonSerializer : public Serializer {
public:
	JsonSerializer(std::ostream& outputStream);

	void serialize(const Value& value) override;
	void serialize(const Number& number) override;
	void serialize(const String& string) override;
	void serialize(const Boolean& boolean) override;
	void serialize(const Array& array) override;
	void serialize(const Object& object) override;
	void serialize(const Null& null) override;

	void setOutputStream(std::ostream& outputStream);

private:
	void startNewLine();

	std::ostream* outputStream;
	unsigned tabs = 0;
};

}