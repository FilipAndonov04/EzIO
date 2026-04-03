#pragma once
#include "EzIO/Exception/Value/ValueException.h"

namespace EzIO {

class ConversionException : public ValueException {
public:
	explicit ConversionException(const char* msg);
	explicit ConversionException(const std::string& msg);
};

}