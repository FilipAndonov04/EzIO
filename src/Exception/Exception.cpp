#include "EzIO/Exception/Exception.h"

namespace ezio {

Exception::Exception(const char* msg)
	: std::exception(msg) {}

Exception::Exception(const std::string& msg)
	: Exception(msg.c_str()) {}

}