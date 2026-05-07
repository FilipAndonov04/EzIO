#pragma once

#include <string>

#include "EzIO/IO/Json/Tokenizer/TokenType.hpp"

namespace ezio {

struct JsonToken {
	JsonTokenType type;
	std::string payload;
};

}