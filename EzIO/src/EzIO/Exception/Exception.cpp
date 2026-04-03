#include "Exception.h"

namespace EzIO {

Exception::Exception(const char* msg)
	: std::exception(msg) {}

Exception::Exception(const std::string& msg)
	: Exception(msg.c_str()) {}

}