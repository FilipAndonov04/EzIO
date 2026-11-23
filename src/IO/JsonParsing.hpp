#pragma once

#include <string>
#include <variant>
#include <ios>

namespace ezio {

enum class JsonTokenType {
	Text,
	Number,
	True,
	False,
	Null,
	OpenCurlyBracket,
	CloseCurlyBracket,
	OpenSquareBracket,
	CloseSquareBracket,
	Colon,
	Comma
};

struct JsonToken {
	JsonTokenType type;
	std::variant<double, std::string> payload;
};

JsonToken parseJsonToken(std::istream& is);

}