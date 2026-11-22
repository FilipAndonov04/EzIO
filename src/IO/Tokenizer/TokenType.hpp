#pragma once

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

}