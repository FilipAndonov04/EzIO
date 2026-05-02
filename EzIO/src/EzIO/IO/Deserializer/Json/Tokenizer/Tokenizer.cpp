#include "Tokenizer.h"
#include "EzIO/Exception/IO/IOException.h"
#include "EzIO/IO/ConstantStrings/Json/JsonConstants.h"

#include <sstream>

namespace ezio {

constexpr char ERROR_MESSAGE_INPUT_STREAM_ENDED[] = "input stream ended";

JsonToken JsonTokenizer::parseToken(std::istream& is) const {
	char ch;
	if (!(is >> ch)) {
		throw InputException(ERROR_MESSAGE_INPUT_STREAM_ENDED);
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

JsonToken JsonTokenizer::parseSign(char sign) const {
	JsonToken token = [](char sign) {
		switch (sign) {
		case '{':
			return JsonToken{JsonTokenType::OpenCurlyBracket, "{"};
		case '}':
			return JsonToken{JsonTokenType::CloseCurlyBracket, "}"};
		case '[':
			return JsonToken{JsonTokenType::OpenSquareBracket, "["};
		case ']':
			return JsonToken{JsonTokenType::CloseSquareBracket, "]"};
		case ':':
			return JsonToken{JsonTokenType::Colon, ":"};
		case ',':
			return JsonToken{JsonTokenType::Comma, ","};
		default:
			throw InputException("invalid token sign");
		}
	}(sign);
	return token;
}

JsonToken JsonTokenizer::parseText(std::istream& is) const {
	std::string result;

	bool isEscaped = false;
	while (true) {
		char ch;
		if (!(is >> ch)) {
			throw InputException("text does not have a closing quote");
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
				throw InputException("invalid escaped character");
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

	return JsonToken{JsonTokenType::Text, std::move(result)};
}

JsonToken JsonTokenizer::parseNumber(std::istream& is) const {
	double num;
	if (!(is >> num)) {
		throw InputException("could not read a number");
	}

	return JsonToken{JsonTokenType::Number, std::to_string(num)};
}

JsonToken JsonTokenizer::parseKeyword(std::string_view keyword) const {
	if (keyword == JSON_CONSTANT_TRUE) {
		return JsonToken{JsonTokenType::True, std::string(JSON_CONSTANT_TRUE)};
	} if (keyword == JSON_CONSTANT_FALSE) {
		return JsonToken{JsonTokenType::False, std::string(JSON_CONSTANT_FALSE)};
	} else if (keyword == JSON_CONSTANT_NULL) {
		return JsonToken{JsonTokenType::Null, std::string(JSON_CONSTANT_NULL)};
	}

	throw InputException("invalid token");
}

bool JsonTokenizer::isSign(char sign) const {
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

bool JsonTokenizer::isDigit(char ch) const {
	return ch >= '0' && ch <= '9';
}

bool JsonTokenizer::isDash(char ch) const {
	return ch == '-';
}

bool JsonTokenizer::isQuote(char ch) const {
	return ch == '\"';
}

std::string JsonTokenizer::readKeyword(std::istream& is) const {
	std::string res;
	while (true) {
		char ch;
		if (!is.get(ch)) {
			throw InputException(ERROR_MESSAGE_INPUT_STREAM_ENDED);
		}

		if (ch < 'a' || ch > 'z') {
			is.unget();
			return res;
		}

		res.push_back(ch);
	}
}

}