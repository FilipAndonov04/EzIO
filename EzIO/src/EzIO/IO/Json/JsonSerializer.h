#pragma once

#include <ios>

#include "EzIO/IO/Serializer.h"

namespace ezio {

class JsonSerializer : public Serializer {
public:
	JsonSerializer(std::ostream& outputStream);

	void serialize(const Value& value) override;
	void serialize(double number) override;
	void serialize(bool boolean) override;
	void serialize(const std::string& string) override;
	void serialize(const Array& array) override;
	void serialize(const Object& object) override;

	void setOutputStream(std::ostream& outputStream);

private:
	void startNewLine();

private:
	std::ostream* outputStream;
	unsigned tabs = 0;
};

}