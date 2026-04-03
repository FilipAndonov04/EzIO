#pragma once

namespace EzIO {

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