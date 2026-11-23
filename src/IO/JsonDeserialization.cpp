#include "IO/JsonDeserialization.hpp"

#include "IO/JsonConstants.hpp"
#include "IO/JsonParsing.hpp"
#include "Details/Verify.hpp"

namespace ezio {

static Value createJsonValue(JsonToken token, std::istream& is);

static double createJsonNumber(JsonToken token) {
	verify(token.type == JsonTokenType::Number, "invalid token");
	return std::get<double>(token.payload);
}

static std::string createJsonString(JsonToken token) {
	verify(token.type == JsonTokenType::Text, "invalid token");
	return std::move(std::get<std::string>(token.payload));
}

static bool createJsonBoolean(JsonToken token) {
	static const std::string ERROR_MESSAGE_BOOLEAN_VALID_VALUES = "boolean value must be " +
		std::string(JSON_CONSTANT_TRUE) + " or " + std::string(JSON_CONSTANT_FALSE);

	verify(token.type == JsonTokenType::True || token.type == JsonTokenType::False,
		   ERROR_MESSAGE_BOOLEAN_VALID_VALUES.c_str());
	return token.type == JsonTokenType::True;
}

static Array createJsonArray(JsonToken token, std::istream& is) {
	verify(token.type == JsonTokenType::OpenSquareBracket, "array must start with an open bracket");
	Array array;

	token = parseJsonToken(is);
	if (token.type == JsonTokenType::CloseSquareBracket) {
		return array;
	}

	while (true) {
		array.pushBack(createJsonValue(std::move(token), is));

		token = parseJsonToken(is);
		if (token.type == JsonTokenType::CloseSquareBracket) {
			return array;
		}
		verify(token.type == JsonTokenType::Comma, "array must separate its elements with a comma");

		token = parseJsonToken(is);
	}
}

static Object createJsonObject(JsonToken token, std::istream& is) {
	verify(token.type == JsonTokenType::OpenCurlyBracket, "object must start with a curly bracket");
	Object object;

	token = parseJsonToken(is);
	if (token.type == JsonTokenType::CloseCurlyBracket) {
		return object;
	}

	while (true) {
		verify(token.type == JsonTokenType::Text, "object member stats with its name");
		std::string memberName = std::move(std::get<std::string>(token.payload));

		token = parseJsonToken(is);
		verify(token.type == JsonTokenType::Colon, "object member is followed with a colon");

		token = parseJsonToken(is);
		object.addMember(memberName, createJsonValue(std::move(token), is));

		token = parseJsonToken(is);
		if (token.type == JsonTokenType::CloseCurlyBracket) {
			return object;
		}
		verify(token.type == JsonTokenType::Comma, "object must separate its members with a comma");

		token = parseJsonToken(is);
	}
}

static Value createJsonValue(JsonToken token, std::istream& is) {
	switch (token.type) {
	case JsonTokenType::Number:
		return createJsonNumber(std::move(token));
	case JsonTokenType::Text:
		return createJsonString(std::move(token));
	case JsonTokenType::True:
	case JsonTokenType::False:
		return createJsonBoolean(std::move(token));
	case JsonTokenType::OpenSquareBracket:
		return createJsonArray(std::move(token), is);
	case JsonTokenType::OpenCurlyBracket:
		return createJsonObject(std::move(token), is);
	case JsonTokenType::Null:
		return Value();
	default:
		throw std::runtime_error("invalid token");
	}
}

Value deserializeJson(std::istream& is) {
	return createJsonValue(parseJsonToken(is), is);
}

}