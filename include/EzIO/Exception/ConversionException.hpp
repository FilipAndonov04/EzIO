#pragma once

#include "EzIO/Exception/Exception.hpp"

namespace ezio {

class ConversionException : public Exception {
public:
	explicit ConversionException(const char* msg);
	explicit ConversionException(const std::string& msg);
};

}