#include "JsonSerializer.h"

#include "EzIO/IO/ConstantStrings/Json/JsonConstants.h"
#include "EzIO/Value/Value.h"
#include "EzIO/Value/Array/Array.h"
#include "EzIO/Value/Object/Object.h"
#include "EzIO/Exception/IOException.h"

#include <iostream>

namespace ezio {

JsonSerializer::JsonSerializer(std::ostream& outputStream) 
	: outputStream(&outputStream) {}

void JsonSerializer::serialize(const Value& value) {
	if (value.isNumber()) {
		serialize(value.asNumber());
	} else if (value.isBoolean()) {
		serialize(value.asBoolean());
	} else if (value.isString()) {
		serialize(value.asString());
	} else if (value.isArray()) {
		serialize(value.asArray());
	} else if (value.isObject()) {
		serialize(value.asObject());
	} else if (value.isNull()) {
		(*outputStream) << JSON_CONSTANT_NULL;
	} else {
		throw IOException("invalid value");
	}
}

void JsonSerializer::serialize(double number) { 
	(*outputStream) << number; 
}

void JsonSerializer::serialize(const std::string& string) {
	(*outputStream) << '\"'; 

	size_t length = string.length();
	for (size_t i = 0; i < length; i++) {
		char cur = string[i];

		switch (cur) {
		case '\n':
			(*outputStream) << "\\n";
			break;
		case '\t':
			(*outputStream) << "\\t";
			break;
		case '\\':
			(*outputStream) << "\\\\";
			break;
		case '\"':
			(*outputStream) << "\\\"";
			break;
		default:
			(*outputStream) << cur;
			break;
		}
	}

	(*outputStream) << '\"';
}

void JsonSerializer::serialize(bool boolean) {
	std::string_view text = boolean ? JSON_CONSTANT_TRUE : JSON_CONSTANT_FALSE;
	(*outputStream) << text;
}

void JsonSerializer::serialize(const Array& array) {
	if (array.isEmpty()) {
		(*outputStream) << "[]";
		return;
	}

	(*outputStream) << "[\n";
	tabs++;

	for (size_t i = 0; i < array.getSize(); i++) {
		startNewLine();
		serialize(array[i]);
		
		if (i != array.getSize() - 1) {
			(*outputStream) << ',';
		}
		(*outputStream) << '\n';
	}

	tabs--;
	startNewLine();
	(*outputStream) << ']';
}

void JsonSerializer::serialize(const Object& object) {
	if (object.getMemberCount() == 0) {
		(*outputStream) << "{}";
		return;
	}

	(*outputStream) << "{\n";
	tabs++;

	size_t iterated = 0;
	for (const auto& member : object) {
		startNewLine();
		(*outputStream) << '\"' << member.first << "\": ";
		serialize(member.second);

		if (++iterated != object.getMemberCount()) {
			(*outputStream) << ',';
		}
		(*outputStream) << '\n';
	}

	tabs--;
	startNewLine();
	(*outputStream) << "}";
}

void JsonSerializer::setOutputStream(std::ostream& outputStream) {
	this->outputStream = &outputStream;
}

void JsonSerializer::startNewLine() {
	unsigned t = tabs;
	while (t-- > 0) {
		(*outputStream) << '\t';
	}
}

}