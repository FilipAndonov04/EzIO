#include "JsonSerializer.h"
#include "EzIO/IO/ConstantStrings/Json/JsonConstants.h"
#include "EzIO/Value/Value.h"
#include "EzIO/Value/Number/Number.h"
#include "EzIO/Value/String/String.h"
#include "EzIO/Value/Boolean/Boolean.h"
#include "EzIO/Value/Array/Array.h"
#include "EzIO/Value/Object/Object.h"
#include "EzIO/Value/Null/Null.h"

#include <iostream>

namespace EzIO {

JsonSerializer::JsonSerializer(std::ostream& outputStream) 
	: outputStream(&outputStream) {}

void JsonSerializer::serialize(const Value& value) {
	value.acceptSerializer(*this);
}

void JsonSerializer::serialize(const Number& number) { 
	(*outputStream) << number.getData(); 
}

void JsonSerializer::serialize(const String& string) {
	(*outputStream) << '\"'; 

	size_t length = string.getData().length();
	for (size_t i = 0; i < length; i++) {
		char cur = string.getData()[i];

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

void JsonSerializer::serialize(const Boolean& boolean) {
	std::string_view text = boolean.getData() ? JSON_CONSTANT_TRUE : JSON_CONSTANT_FALSE;
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
		serialize(array.at(i));
		
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
	const auto& members = object.getMembers();
	if (members.empty()) {
		(*outputStream) << "{}";
		return;
	}

	(*outputStream) << "{\n";
	tabs++;

	size_t iterated = 0;
	for (const auto& member : members) {
		startNewLine();
		(*outputStream) << '\"' << member.first << "\": ";
		serialize(*member.second);

		if (++iterated != members.size()) {
			(*outputStream) << ',';
		}
		(*outputStream) << '\n';
	}

	tabs--;
	startNewLine();
	(*outputStream) << "}";
}

void JsonSerializer::serialize(const Null& null) {
	(*outputStream) << JSON_CONSTANT_NULL;
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