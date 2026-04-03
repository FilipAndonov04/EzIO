#include "ValueConversionException.h"

namespace EzIO {

ValueConversionException::ValueConversionException(const char* msg)
	: ValueException(msg) {}

ValueConversionException::ValueConversionException(const std::string& msg)
	: ValueException(msg) {}

}