#pragma once

#include "EzIO/Exception/Exception.h"

namespace ezio {

class IOException : public Exception {
public:
	explicit IOException(const char* msg);
	explicit IOException(const std::string& msg);
};

}