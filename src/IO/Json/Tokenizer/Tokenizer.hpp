#pragma once

#include "IO/Json/Tokenizer/Token.hpp"

namespace ezio {

class JsonTokenizer {
public:
	JsonToken parseToken(std::istream& is) const;

private:
	JsonToken parseSign(char sign) const;
	JsonToken parseText(std::istream& is) const;
	JsonToken parseNumber(std::istream& is) const;
	JsonToken parseKeyword(std::string_view keyword) const;

	bool isSign(char ch) const;
	bool isDigit(char ch) const;
	bool isDash(char ch) const;
	bool isQuote(char ch) const;
	std::string readKeyword(std::istream& is) const;
};

}