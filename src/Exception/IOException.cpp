#include "EzIO/Exception/IOException.hpp"

namespace ezio {

IOException::IOException(const char* msg)
	: Exception(msg) {}

IOException::IOException(const std::string& msg)
	: Exception(msg) {}

}