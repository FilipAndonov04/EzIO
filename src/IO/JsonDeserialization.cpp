#include "IO/JsonDeserialization.hpp"

#include "IO/JsonConstants.hpp"
#include "IO/JsonParsing.hpp"

namespace ezio {

static void assertTokenType(JsonTokenType expected, JsonTokenType actual, const char* msg) {
	if (actual != expected) {
		throw std::exception(msg);
	}
}

static void assertTokenType(JsonTokenType expected, JsonTokenType actual) {
	assertTokenType(expected, actual, "invalid token");
}

static void assertTokenType(JsonTokenType expected1, JsonTokenType expected2,
							JsonTokenType actual, const char* msg) {
	if (actual != expected1 && actual != expected2) {
		throw std::exception(msg);
	}
}

static void assertTokenType(JsonTokenType expected1, JsonTokenType expected2, JsonTokenType actual) {
	assertTokenType(expected1, expected2, actual, "invalid token");
}

static Value createJsonValue(JsonToken token, std::istream& is);

static double createJsonNumber(JsonToken token) {
	assertTokenType(JsonTokenType::Number, token.type);
	return std::stod(token.payload);
}

static std::string createJsonString(JsonToken token) {
	assertTokenType(JsonTokenType::Text, token.type,
					"string must start with a quote");
	return std::move(token.payload);
}

static bool createJsonBoolean(JsonToken token) {
	static const std::string ERROR_MESSAGE_BOOLEAN_VALID_VALUES = "boolean value must be " +
		std::string(JSON_CONSTANT_TRUE) + " or " + std::string(JSON_CONSTANT_FALSE);

	assertTokenType(JsonTokenType::True, JsonTokenType::False, token.type,
					ERROR_MESSAGE_BOOLEAN_VALID_VALUES.c_str());
	return token.type == JsonTokenType::True;
}

static Array createJsonArray(JsonToken token, std::istream& is) {
	assertTokenType(JsonTokenType::OpenSquareBracket, token.type,
					"array must start with an open bracket");
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
		assertTokenType(JsonTokenType::Comma, token.type,
						"array must separate its elements with a comma");

		token = parseJsonToken(is);
	}
}

static Object createJsonObject(JsonToken token, std::istream& is) {
	assertTokenType(JsonTokenType::OpenCurlyBracket, token.type,
					"object must start with a curly bracket");
	Object object;

	token = parseJsonToken(is);
	if (token.type == JsonTokenType::CloseCurlyBracket) {
		return object;
	}

	while (true) {
		assertTokenType(JsonTokenType::Text, token.type,
						"object member stats with its name");
		std::string memberName = std::move(token.payload);

		token = parseJsonToken(is);
		assertTokenType(JsonTokenType::Colon, token.type,
						"object member is followed with a colon");

		token = parseJsonToken(is);
		object.addMember(memberName, createJsonValue(std::move(token), is));

		token = parseJsonToken(is);
		if (token.type == JsonTokenType::CloseCurlyBracket) {
			return object;
		}
		assertTokenType(JsonTokenType::Comma, token.type,
						"object must separate its members with a comma");

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
		throw std::exception("invalid token");
	}
}

Value deserializeJson(std::istream& is) {
	return createJsonValue(parseJsonToken(is), is);
}

}