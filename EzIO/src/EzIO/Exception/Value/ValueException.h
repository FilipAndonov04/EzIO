#pragma once
#include "EzIO/Exception/Exception.h"

namespace ezio {

class ValueException : public Exception {
public:
	explicit ValueException(const char* msg);
	explicit ValueException(const std::string& msg);
};

}