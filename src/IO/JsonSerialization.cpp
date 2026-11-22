#include "IO/JsonSerialization.hpp"

#include <ostream>

#include "Value/Value.hpp"
#include "IO/JsonConstants.hpp"

namespace ezio {

static unsigned tabs = 0;

static void startNewLine(std::ostream& os) {
	unsigned t = tabs;
	while (t-- > 0) {
		os << '\t';
	}
}

void serializeJson(std::ostream& os, const Value& value) {
	if (value.isNumber()) {
		serializeJson(os, value.asNumber());
	} else if (value.isBoolean()) {
		serializeJson(os, value.asBoolean());
	} else if (value.isString()) {
		serializeJson(os, value.asString());
	} else if (value.isArray()) {
		serializeJson(os, value.asArray());
	} else if (value.isObject()) {
		serializeJson(os, value.asObject());
	} else if (value.isNull()) {
		os << JSON_CONSTANT_NULL;
	} else {
		throw std::runtime_error("invalid value");
	}
}

void serializeJson(std::ostream& os, double number) {
	os << number;
}

void serializeJson(std::ostream& os, const std::string& string) {
	os << '\"';

	for (char cur : string) {
		switch (cur) {
		case '\n':
			os << "\\n";
			break;
		case '\t':
			os << "\\t";
			break;
		case '\\':
			os << "\\\\";
			break;
		case '\"':
			os << "\\\"";
			break;
		default:
			os << cur;
			break;
		}
	}

	os << '\"';
}

void serializeJson(std::ostream& os, bool boolean) {
	std::string_view text = boolean ? JSON_CONSTANT_TRUE : JSON_CONSTANT_FALSE;
	os << text;
}

void serializeJson(std::ostream& os, const Array& array) {
	if (array.isEmpty()) {
		os << "[]";
		return;
	}

	os << "[\n";
	tabs++;

	for (size_t i = 0; i < array.size(); i++) {
		startNewLine(os);
		serializeJson(os, array[i]);
		
		if (i != array.size() - 1) {
			os << ',';
		}
		os << '\n';
	}

	tabs--;
	startNewLine(os);
	os << ']';
}

void serializeJson(std::ostream& os, const Object& object) {
	if (object.isEmpty() == 0) {
		os << "{}";
		return;
	}

	os << "{\n";
	tabs++;

	size_t iterated = 0;
	for (const auto& member : object) {
		startNewLine(os);
		os << '\"' << member.first << "\": ";
		serializeJson(os, member.second);

		if (++iterated != object.size()) {
			os << ',';
		}
		os << '\n';
	}

	tabs--;
	startNewLine(os);
	os << "}";
}

}