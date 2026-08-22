#pragma once

#include <string>

#include "IO/Json/Tokenizer/TokenType.hpp"

namespace ezio {

struct JsonToken {
	JsonTokenType type;
	std::string payload;
};

}