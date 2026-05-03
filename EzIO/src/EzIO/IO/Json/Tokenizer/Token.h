#pragma once

#include <string>

#include "EzIO/IO/Json/Tokenizer/TokenType.h"

namespace ezio {

struct JsonToken {
	JsonTokenType type;
	std::string payload;
};

}