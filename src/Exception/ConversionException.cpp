#include "EzIO/Exception/ConversionException.h"

namespace ezio {

ConversionException::ConversionException(const char* msg)
	: Exception(msg) {}

ConversionException::ConversionException(const std::string& msg)
	: Exception(msg) {}

}