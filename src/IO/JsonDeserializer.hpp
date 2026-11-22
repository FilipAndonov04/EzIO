#pragma once

#include <ios>

#include "Value/Value.hpp"
#include "IO/Tokenizer/Tokenizer.hpp"

namespace ezio {

class JsonDeserializer {
public:
	JsonDeserializer(std::istream& inputStream);

	Value deserialize();
	double deserializeNumber();
	std::string deserializeString();
	bool deserializeBoolean();
	Array deserializeArray();
	Object deserializeObject();

	void setInputStream(std::istream& inputStream);

private:
	Value createValue(JsonToken token);
	double createNumber(JsonToken token);
	std::string createString(JsonToken token);
	bool createBoolean(JsonToken token);
	Array createArray(JsonToken token);
	Object createObject(JsonToken token);

	void assertTokenType(JsonTokenType expected, JsonTokenType actual) const;
	void assertTokenType(JsonTokenType expected, JsonTokenType actual,
						 const char* errorMessage) const;
	void assertTokenType(JsonTokenType expected1, JsonTokenType expected2, 
						 JsonTokenType actual) const;
	void assertTokenType(JsonTokenType expected1, JsonTokenType expected2, 
						 JsonTokenType actual, const char* errorMessage) const;

private:
	std::istream* inputStream;
	JsonTokenizer tokenizer;
};

}