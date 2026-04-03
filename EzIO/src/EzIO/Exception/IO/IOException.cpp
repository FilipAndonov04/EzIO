#include "IOException.h"

namespace EzIO {

IOException::IOException(const char* msg)
	: Exception(msg) {}

IOException::IOException(const std::string& msg)
	: Exception(msg) {}

InputException::InputException(const char* msg) 
	: InputException(std::string(msg)) {}

InputException::InputException(const std::string& msg) 
	: IOException("input exception: " + msg) {}

OutputException::OutputException(const char* msg) 
	: OutputException(std::string(msg)) {}

OutputException::OutputException(const std::string& msg) 
	: IOException("output exception: " + msg) {}

}