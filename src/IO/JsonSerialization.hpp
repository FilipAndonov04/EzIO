#pragma once

#include <ios>
#include <string_view>

namespace ezio {

class Value;
class Array;
class Object;

void serializeJson(std::ostream& os, const Value& value);
void serializeJson(std::ostream& os, double number);
void serializeJson(std::ostream& os, bool boolean);
void serializeJson(std::ostream& os, std::string_view string);
void serializeJson(std::ostream& os, const Array& array);
void serializeJson(std::ostream& os, const Object& object);

}