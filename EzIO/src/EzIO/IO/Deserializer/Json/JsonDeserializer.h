#pragma once
#include "EzIO/IO/Deserializer/Deserializer.h"
#include "EzIO/IO/Deserializer/Json/Tokenizer/Tokenizer.h"

#include <ios>

namespace EzIO {

class JsonDeserializer : public Deserializer {
public:
	JsonDeserializer(std::istream& inputStream);

	std::unique_ptr<Value> deserialize() override;
	std::unique_ptr<Number> deserializeNumber() override;
	std::unique_ptr<String> deserializeString() override;
	std::unique_ptr<Boolean> deserializeBoolean() override;
	std::unique_ptr<Array> deserializeArray() override;
	std::unique_ptr<Object> deserializeObject() override;
	std::unique_ptr<Null> deserializeNull() override;

	void setInputStream(std::istream& inputStream);

private:
	std::unique_ptr<Value> createValue(JsonToken token);
	std::unique_ptr<Number> createNumber(JsonToken token);
	std::unique_ptr<String> createString(JsonToken token);
	std::unique_ptr<Boolean> createBoolean(JsonToken token);
	std::unique_ptr<Array> createArray(JsonToken token);
	std::unique_ptr<Object> createObject(JsonToken token);
	std::unique_ptr<Null> createNull(JsonToken token);

	void verifyTokenType(JsonTokenType expected, JsonTokenType actual) const;
	void verifyTokenType(JsonTokenType expected, JsonTokenType actual,
						 const char* errorMessage) const;
	void verifyTokenType(JsonTokenType expected1, JsonTokenType expected2, 
						 JsonTokenType actual) const;
	void verifyTokenType(JsonTokenType expected1, JsonTokenType expected2, 
						 JsonTokenType actual, const char* errorMessage) const;

	std::istream* inputStream;
	JsonTokenizer tokenizer;
};

}