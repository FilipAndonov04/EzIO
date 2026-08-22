#include "Exception/ConversionException.hpp"

namespace ezio {

ConversionException::ConversionException(const char* msg)
	: Exception(msg) {}

ConversionException::ConversionException(const std::string& msg)
	: Exception(msg) {}

}