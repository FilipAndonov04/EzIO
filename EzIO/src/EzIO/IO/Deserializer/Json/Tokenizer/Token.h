#pragma once
#include "EzIO/IO/Deserializer/Json/Tokenizer/TokenType.h"

#include <string>

namespace ezio {

struct JsonToken {
	JsonTokenType type;
	std::string payload;
};

}