#pragma once

#include <stdexcept>

namespace EzIO {

class Exception : public std::exception {
public:
	explicit Exception(const char* msg);
	explicit Exception(const std::string& msg);
};

}