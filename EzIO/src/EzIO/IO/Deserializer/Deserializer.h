#pragma once
#include "EzIO/Value/Value.h"
#include "EzIO/Value/Number/Number.h"
#include "EzIO/Value/String/String.h"
#include "EzIO/Value/Boolean/Boolean.h"
#include "EzIO/Value/Array/Array.h"
#include "EzIO/Value/Object/Object.h"
#include "EzIO/Value/Null/Null.h"

#include <memory>

namespace EzIO {

class Deserializer {
public:
	virtual std::unique_ptr<Value> deserialize() = 0;
	virtual std::unique_ptr<Number> deserializeNumber() = 0;
	virtual std::unique_ptr<String> deserializeString() = 0;
	virtual std::unique_ptr<Boolean> deserializeBoolean() = 0;
	virtual std::unique_ptr<Array> deserializeArray() = 0;
	virtual std::unique_ptr<Object> deserializeObject() = 0;
	virtual std::unique_ptr<Null> deserializeNull() = 0;
};

}