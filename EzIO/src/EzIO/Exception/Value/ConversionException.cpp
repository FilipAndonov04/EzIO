#include "ConversionException.h"

namespace EzIO {

ConversionException::ConversionException(const char* msg)
	: ValueException(msg) {}

ConversionException::ConversionException(const std::string& msg)
	: ValueException(msg) {}

}