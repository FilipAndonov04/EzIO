#pragma once

#include <string>

#include "IO/Tokenizer/TokenType.hpp"

namespace ezio {

struct JsonToken {
	JsonTokenType type;
	std::string payload;
};

}