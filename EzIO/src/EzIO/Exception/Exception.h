#pragma once

#include <stdexcept>

namespace ezio {

class Exception : public std::exception {
public:
	explicit Exception(const char* msg);
	explicit Exception(const std::string& msg);
};

}