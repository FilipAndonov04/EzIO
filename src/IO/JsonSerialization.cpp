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
	if (const double* num = value.asNumber()) {
		serializeJson(os, *num);
	} else if (const bool* b = value.asBoolean()) {
		serializeJson(os, *b);
	} else if (const std::string* str = value.asString()) {
		serializeJson(os, std::string_view(*str));
	} else if (const Array* arr = value.asArray()) {
		serializeJson(os, *arr);
	} else if (const Object* obj = value.asObject()) {
		serializeJson(os, *obj);
	} else if (value.isNull()) {
		os << JSON_CONSTANT_NULL;
	} else {
		throw std::runtime_error("invalid value");
	}
}

void serializeJson(std::ostream& os, double number) {
	os << number;
}

void serializeJson(std::ostream& os, std::string_view string) {
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
	if (object.isEmpty()) {
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