#pragma once
#include "EzIO/Exception/Value/ValueException.h"

namespace EzIO {

class ValueConversionException : public ValueException {
public:
	explicit ValueConversionException(const char* msg);
	explicit ValueConversionException(const std::string& msg);
};

}