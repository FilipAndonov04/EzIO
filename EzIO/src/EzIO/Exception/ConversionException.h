#pragma once

#include "EzIO/Exception/Exception.h"

namespace ezio {

class ConversionException : public Exception {
public:
	explicit ConversionException(const char* msg);
	explicit ConversionException(const std::string& msg);
};

}