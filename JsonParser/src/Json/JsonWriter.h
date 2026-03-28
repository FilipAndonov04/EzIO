#pragma once

#include <ios>

namespace Json {

class JsonWriter {
public:
	void writeNumber(std::ostream& os, double number) const;
	void writeString(std::ostream& os, std::string_view string) const;
	void writeBool(std::ostream& os, bool value) const;
};

}