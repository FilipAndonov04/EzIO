#include "JsonDeserializer.h"
#include "EzIO/Exception/IO/IOException.h"
#include "EzIO/IO/ConstantStrings/Json/JsonConstants.h"

namespace EzIO {

JsonDeserializer::JsonDeserializer(std::istream& inputStream) 
	: inputStream(&inputStream) {}

std::unique_ptr<Value> JsonDeserializer::deserialize() {
	return createValue(tokenizer.parseToken(*inputStream));
}

std::unique_ptr<Number> JsonDeserializer::deserializeNumber() {
	return createNumber(tokenizer.parseToken(*inputStream));
}

std::unique_ptr<String> JsonDeserializer::deserializeString() {
	return createString(tokenizer.parseToken(*inputStream));
}

std::unique_ptr<Boolean> JsonDeserializer::deserializeBoolean() {
	return createBoolean(tokenizer.parseToken(*inputStream));
}

std::unique_ptr<Array> JsonDeserializer::deserializeArray() {
	return createArray(tokenizer.parseToken(*inputStream));
}

std::unique_ptr<Object> JsonDeserializer::deserializeObject() {
	return createObject(tokenizer.parseToken(*inputStream));
}

std::unique_ptr<Null> JsonDeserializer::deserializeNull() {
	return createNull(tokenizer.parseToken(*inputStream));
}

void JsonDeserializer::setInputStream(std::istream& inputStream) {
	this->inputStream = &inputStream;
}

std::unique_ptr<Value> JsonDeserializer::createValue(JsonToken token) {
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
		return createNull(std::move(token));
	default:
		throw InputException("invalid token");
	}
}

std::unique_ptr<Number> JsonDeserializer::createNumber(JsonToken token) {
	verifyTokenType(JsonTokenType::Number, token.type);

	return Number::of(std::stod(token.payload));
}

std::unique_ptr<String> JsonDeserializer::createString(JsonToken token) {
	verifyTokenType(JsonTokenType::Text, token.type,
					"string must start with a quote");

	return String::of(std::move(token.payload));
}

std::unique_ptr<Boolean> JsonDeserializer::createBoolean(JsonToken token) {
	static const std::string ERROR_MESSAGE_BOOLEAN_VALID_VALUES = "boolean value must be " + 
		std::string(JSON_CONSTANT_TRUE) + " or " + std::string(JSON_CONSTANT_FALSE);

	verifyTokenType(JsonTokenType::True, JsonTokenType::False, token.type, 
					ERROR_MESSAGE_BOOLEAN_VALID_VALUES.c_str());

	return Boolean::of(token.type == JsonTokenType::True);
}

std::unique_ptr<Array> JsonDeserializer::createArray(JsonToken token) {
	verifyTokenType(JsonTokenType::OpenSquareBracket, token.type,
					"array must start with an open bracket");

	auto array = std::make_unique<Array>();

	token = tokenizer.parseToken(*inputStream);
	if (token.type == JsonTokenType::CloseSquareBracket) {
		return array;
	}

	while (true) {
		array->pushBack(createValue(std::move(token)));

		token = tokenizer.parseToken(*inputStream);
		if (token.type == JsonTokenType::CloseSquareBracket) {
			return array;
		} 
		verifyTokenType(JsonTokenType::Comma, token.type,
			   "array must separate its elements with a comma");

		token = tokenizer.parseToken(*inputStream);
	}
}

std::unique_ptr<Object> JsonDeserializer::createObject(JsonToken token) {
	verifyTokenType(JsonTokenType::OpenCurlyBracket, token.type,
					"object must start with a curly bracket");
	
	auto object = std::make_unique<Object>();

	token = tokenizer.parseToken(*inputStream);
	if (token.type == JsonTokenType::CloseCurlyBracket) {
		return object;
	}

	while (true) {
		verifyTokenType(JsonTokenType::Text, token.type,
						"object member stats with its name");
		std::string memberName = std::move(token.payload);

		token = tokenizer.parseToken(*inputStream);
		verifyTokenType(JsonTokenType::Colon, token.type,
						"object member is followed with a colon");

		token = tokenizer.parseToken(*inputStream);
		object->addMember(memberName, createValue(std::move(token)));

		token = tokenizer.parseToken(*inputStream);
		if (token.type == JsonTokenType::CloseCurlyBracket) {
			return object;
		}
		verifyTokenType(JsonTokenType::Comma, token.type,
						"object must separate its members with a comma");

		token = tokenizer.parseToken(*inputStream);
	}
}

std::unique_ptr<Null> JsonDeserializer::createNull(JsonToken token) {
	verifyTokenType(JsonTokenType::Null, token.type);

	return Null::of();
}

void JsonDeserializer::verifyTokenType(JsonTokenType expected, JsonTokenType actual) const {
	verifyTokenType(expected, actual, "invalid token");
}

void JsonDeserializer::verifyTokenType(JsonTokenType expected, JsonTokenType actual, 
									   const char* errorMessage) const {
	if (actual != expected) {
		throw InputException(errorMessage);
	}
}

void JsonDeserializer::verifyTokenType(JsonTokenType expected1, JsonTokenType expected2, 
									   JsonTokenType actual) const {
	verifyTokenType(expected1, expected2, actual, "invalid token");
}

void JsonDeserializer::verifyTokenType(JsonTokenType expected1, JsonTokenType expected2, 
									   JsonTokenType actual, const char* errorMessage) const {
	if (actual != expected1 && actual != expected2) {
		throw InputException(errorMessage);
	}
}

}