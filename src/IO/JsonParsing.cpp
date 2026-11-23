#include "IO/JsonParsing.hpp"

#include <istream>
#include <stdexcept>

#include "IO/JsonConstants.hpp"

namespace ezio {

constexpr char ERROR_MESSAGE_INPUT_STREAM_ENDED[] = "input stream ended";

static JsonToken parseSign(char sign) {
	JsonToken token = [](char sign) {
		switch (sign) {
		case '{':
			return JsonToken{JsonTokenType::OpenCurlyBracket};
		case '}':
			return JsonToken{JsonTokenType::CloseCurlyBracket};
		case '[':
			return JsonToken{JsonTokenType::OpenSquareBracket};
		case ']':
			return JsonToken{JsonTokenType::CloseSquareBracket};
		case ':':
			return JsonToken{JsonTokenType::Colon};
		case ',':
			return JsonToken{JsonTokenType::Comma};
		default:
			throw std::runtime_error("invalid token sign");
		}
	}(sign);
	return token;
}

static JsonToken parseText(std::istream& is) {
	JsonToken token{JsonTokenType::Text, std::string{}};
	std::string& result = std::get<std::string>(token.payload);

	bool isEscaped = false;
	while (true) {
		char ch;
		if (!(is >> ch)) {
			throw std::runtime_error("text does not have a closing quote");
		}

		if (isEscaped) {
			switch (ch) {
			case '\\':
				result.push_back('\\');
				break;
			case 'n':
				result.push_back('\n');
				break;
			case 't':
				result.push_back('\t');
				break;
			case '\"':
				result.push_back('\"');
				break;
			default:
				throw std::runtime_error("invalid escaped character");
			}

			isEscaped = false;
			continue;
		}

		if (ch == '\"') {
			break;
		} else if (ch == '\\') {
			isEscaped = true;
			continue;
		} 

		result.push_back(ch);
	}

	return token;
}

static JsonToken parseNumber(std::istream& is) {
	double num;
	if (!(is >> num)) {
		throw std::runtime_error("could not read a number");
	}

	return JsonToken{JsonTokenType::Number, num};
}

static JsonToken parseKeyword(std::string_view keyword) {
	if (keyword == JSON_CONSTANT_TRUE) {
		return JsonToken{JsonTokenType::True};
	} if (keyword == JSON_CONSTANT_FALSE) {
		return JsonToken{JsonTokenType::False};
	} else if (keyword == JSON_CONSTANT_NULL) {
		return JsonToken{JsonTokenType::Null};
	}

	throw std::runtime_error("invalid token");
}

static bool isSign(char sign) {
	switch (sign) {
	case '{':
	case '}':
	case '[':
	case ']':
	case ':':
	case ',':
		return true;
	default:
		return false;
	};
}

static bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

static bool isDash(char ch) {
	return ch == '-';
}

static bool isQuote(char ch) {
	return ch == '\"';
}

static std::string readKeyword(std::istream& is) {
	std::string res;
	while (true) {
		char ch;
		if (!is.get(ch)) {
			return res;
		}

		if (ch < 'a' || ch > 'z') {
			is.unget();
			return res;
		}

		res.push_back(ch);
	}
	return res;
}

JsonToken parseJsonToken(std::istream& is) {
	char ch;
	if (!(is >> ch)) {
		throw std::runtime_error(ERROR_MESSAGE_INPUT_STREAM_ENDED);
	}

	if (isSign(ch)) {
		return parseSign(ch);
	}

	if (isQuote(ch)) {
		return parseText(is);
	}

	is.unget();

	if (isDigit(ch) || isDash(ch)) {
		return parseNumber(is);
	}

	return parseKeyword(readKeyword(is));
}

}