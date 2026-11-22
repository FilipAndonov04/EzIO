#pragma once

#include <string>
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
	std::string payload;
};

JsonToken parseJsonToken(std::istream& is);

}