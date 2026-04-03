#include "ValueException.h"

namespace EzIO {

ValueException::ValueException(const char* msg)
	: Exception(msg) {}

ValueException::ValueException(const std::string& msg)
	: Exception(msg) {}

}