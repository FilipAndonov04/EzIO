#pragma once

#include <ios>

#include "Value/Value.hpp"

namespace ezio {

Value deserializeJson(std::istream& is);

}