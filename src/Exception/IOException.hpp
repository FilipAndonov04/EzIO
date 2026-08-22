#pragma once

#include "Exception/Exception.hpp"

namespace ezio {

class IOException : public Exception {
public:
	explicit IOException(const char* msg);
	explicit IOException(const std::string& msg);
};

}