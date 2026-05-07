#include "EzIO/Exception/IOException.h"

namespace ezio {

IOException::IOException(const char* msg)
	: Exception(msg) {}

IOException::IOException(const std::string& msg)
	: Exception(msg) {}

}