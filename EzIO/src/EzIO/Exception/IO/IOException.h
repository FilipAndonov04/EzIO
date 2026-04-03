#pragma once
#include "EzIO/Exception/Exception.h"

namespace EzIO {

class IOException : public Exception {
public:
	explicit IOException(const char* msg);
	explicit IOException(const std::string& msg);
};

class InputException : public IOException {
public:
	explicit InputException(const char* msg);
	explicit InputException(const std::string& msg);
};

class OutputException : public IOException {
public:
	explicit OutputException(const char* msg);
	explicit OutputException(const std::string& msg);
};

}