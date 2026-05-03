#include "JsonDeserializer.h"

#include "EzIO/Exception/IOException.h"
#include "EzIO/IO/ConstantStrings/Json/JsonConstants.h"

namespace ezio {

JsonDeserializer::JsonDeserializer(std::istream& inputStream) 
	: inputStream(&inputStream) {}

Value JsonDeserializer::deserialize() {
	return createValue(tokenizer.parseToken(*inputStream));
}

double JsonDeserializer::deserializeNumber() {
	return createNumber(tokenizer.parseToken(*inputStream));
}

std::string JsonDeserializer::deserializeString() {
	return createString(tokenizer.parseToken(*inputStream));
}

bool JsonDeserializer::deserializeBoolean() {
	return createBoolean(tokenizer.parseToken(*inputStream));
}

Array JsonDeserializer::deserializeArray() {
	return createArray(tokenizer.parseToken(*inputStream));
}

Object JsonDeserializer::deserializeObject() {
	return createObject(tokenizer.parseToken(*inputStream));
}

void JsonDeserializer::setInputStream(std::istream& inputStream) {
	this->inputStream = &inputStream;
}

Value JsonDeserializer::createValue(JsonToken token) {
	switch (token.type) {
	case JsonTokenType::Number:
		return createNumber(std::move(token));
	case JsonTokenType::Text:
		return createString(std::move(token));
	case JsonTokenType::True:
	case JsonTokenType::False:
		return createBoolean(std::move(token));
	case JsonTokenType::OpenSquareBracket:
		return createArray(std::move(token));
	case JsonTokenType::OpenCurlyBracket:
		return createObject(std::move(token));
	case JsonTokenType::Null:
		return Value();
	default:
		throw IOException("invalid token");
	}
}

double JsonDeserializer::createNumber(JsonToken token) {
	assertTokenType(JsonTokenType::Number, token.type);
	return std::stod(token.payload);
}

std::string JsonDeserializer::createString(JsonToken token) {
	assertTokenType(JsonTokenType::Text, token.type, 
					"string must start with a quote");
	return std::move(token.payload);
}

bool JsonDeserializer::createBoolean(JsonToken token) {
	static const std::string ERROR_MESSAGE_BOOLEAN_VALID_VALUES = "boolean value must be " + 
		std::string(JSON_CONSTANT_TRUE) + " or " + std::string(JSON_CONSTANT_FALSE);

	assertTokenType(JsonTokenType::True, JsonTokenType::False, token.type, 
					ERROR_MESSAGE_BOOLEAN_VALID_VALUES.c_str());
	return token.type == JsonTokenType::True;
}

Array JsonDeserializer::createArray(JsonToken token) {
	assertTokenType(JsonTokenType::OpenSquareBracket, token.type,
					"array must start with an open bracket");
	Array array;

	token = tokenizer.parseToken(*inputStream);
	if (token.type == JsonTokenType::CloseSquareBracket) {
		return array;
	}

	while (true) {
		array.pushBack(createValue(std::move(token)));

		token = tokenizer.parseToken(*inputStream);
		if (token.type == JsonTokenType::CloseSquareBracket) {
			return array;
		} 
		assertTokenType(JsonTokenType::Comma, token.type,
			   "array must separate its elements with a comma");

		token = tokenizer.parseToken(*inputStream);
	}
}

Object JsonDeserializer::createObject(JsonToken token) {
	assertTokenType(JsonTokenType::OpenCurlyBracket, token.type,
					"object must start with a curly bracket");
	Object object;

	token = tokenizer.parseToken(*inputStream);
	if (token.type == JsonTokenType::CloseCurlyBracket) {
		return object;
	}

	while (true) {
		assertTokenType(JsonTokenType::Text, token.type,
						"object member stats with its name");
		std::string memberName = std::move(token.payload);

		token = tokenizer.parseToken(*inputStream);
		assertTokenType(JsonTokenType::Colon, token.type,
						"object member is followed with a colon");

		token = tokenizer.parseToken(*inputStream);
		object.addMember(memberName, createValue(std::move(token)));

		token = tokenizer.parseToken(*inputStream);
		if (token.type == JsonTokenType::CloseCurlyBracket) {
			return object;
		}
		assertTokenType(JsonTokenType::Comma, token.type,
						"object must separate its members with a comma");

		token = tokenizer.parseToken(*inputStream);
	}
}

void JsonDeserializer::assertTokenType(JsonTokenType expected, JsonTokenType actual) const {
	assertTokenType(expected, actual, "invalid token");
}

void JsonDeserializer::assertTokenType(JsonTokenType expected, JsonTokenType actual, 
									   const char* errorMessage) const {
	if (actual != expected) {
		throw IOException(errorMessage);
	}
}

void JsonDeserializer::assertTokenType(JsonTokenType expected1, JsonTokenType expected2, 
									   JsonTokenType actual) const {
	assertTokenType(expected1, expected2, actual, "invalid token");
}

void JsonDeserializer::assertTokenType(JsonTokenType expected1, JsonTokenType expected2, 
									   JsonTokenType actual, const char* errorMessage) const {
	if (actual != expected1 && actual != expected2) {
		throw IOException(errorMessage);
	}
}

}