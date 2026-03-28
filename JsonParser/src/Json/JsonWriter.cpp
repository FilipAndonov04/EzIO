#include "JsonWriter.h"

#include <iostream>

namespace Json {

void JsonWriter::writeNumber(std::ostream& os, double number) const {
	os << number;
}

void JsonWriter::writeString(std::ostream& os, std::string_view string) const {
	os << string;
}

void JsonWriter::writeBool(std::ostream& os, bool value) const {
	os << value;
}

}