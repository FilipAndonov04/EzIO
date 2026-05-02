#include "ConversionException.h"

namespace ezio {

ConversionException::ConversionException(const char* msg)
	: ValueException(msg) {}

ConversionException::ConversionException(const std::string& msg)
	: ValueException(msg) {}

}