#pragma once
#include "EzIO/Value/Value.h"
#include "EzIO/Value/Array/Array.h"
#include "EzIO/Value/Object/Object.h"

namespace ezio {

class Deserializer {
public:
	virtual Value deserialize() = 0;
	virtual double deserializeNumber() = 0;
	virtual std::string deserializeString() = 0;
	virtual bool deserializeBoolean() = 0;
	virtual Array deserializeArray() = 0;
	virtual Object deserializeObject() = 0;
};

}