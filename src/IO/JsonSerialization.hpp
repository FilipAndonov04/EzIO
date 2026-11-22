#pragma once

#include <ios>

namespace ezio {

class Value;
class Array;
class Object;

void serializeJson(std::ostream& os, const Value& value);
void serializeJson(std::ostream& os, double number);
void serializeJson(std::ostream& os, bool boolean);
void serializeJson(std::ostream& os, const std::string& string);
void serializeJson(std::ostream& os, const Array& array);
void serializeJson(std::ostream& os, const Object& object);

}