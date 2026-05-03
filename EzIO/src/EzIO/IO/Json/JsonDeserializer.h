#pragma once

#include <ios>

#include "EzIO/IO/Deserializer.h"
#include "EzIO/IO/Json/Tokenizer/Tokenizer.h"

namespace ezio {

class JsonDeserializer : public Deserializer {
public:
	JsonDeserializer(std::istream& inputStream);

	Value deserialize() override;
	double deserializeNumber() override;
	std::string deserializeString() override;
	bool deserializeBoolean() override;
	Array deserializeArray() override;
	Object deserializeObject() override;

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