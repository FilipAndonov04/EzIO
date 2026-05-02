#include "Value.h"
#include "EzIO/Exception/Value/ConversionException.h"

namespace ezio {

Value::Value(double number)
    : data(number) {}

Value::Value(bool boolean) 
    : data(boolean) {}

Value::Value(std::string string) 
    : data(std::move(string)) {}

Value::Value(Array array) 
    : data(std::move(array)) {}

Value::Value(Object object) 
    : data(std::move(object)) {}

Value& Value::operator=(double number) {
    data = number;
    return *this;
}

Value& Value::operator=(bool boolean) {
    data = boolean;
    return *this;
}

Value& Value::operator=(std::string string) {
    data = std::move(string);
    return *this;
}

Value& Value::operator=(Array array) {
    data = std::move(array);
    return *this;
}

Value& Value::operator=(Object object) {
    data = std::move(object);
    return *this;
}

bool Value::isNull() const {
    return holds_alternative<std::monostate>(data);
}

bool Value::isNumber() const {
    return std::holds_alternative<double>(data);
}

bool Value::isBoolean() const {
    return std::holds_alternative<bool>(data);
}

bool Value::isString() const {
    return std::holds_alternative<std::string>(data);
}

bool Value::isArray() const {
    return std::holds_alternative<Array>(data);
}

bool Value::isObject() const {
    return std::holds_alternative<Object>(data);
}

double Value::asNumber() const {
    assertConversion(isNumber(), "value is not a number");
    return std::get<double>(data);
}

double& Value::asNumber() {
    assertConversion(isNumber(), "value is not a number");
    return std::get<double>(data);
}

bool Value::asBoolean() const {
    assertConversion(isBoolean(), "value is not a boolean");
    return std::get<bool>(data);
}

bool& Value::asBoolean() {
    assertConversion(isBoolean(), "value is not a boolean");
    return std::get<bool>(data);
}

const std::string& Value::asString() const {
    assertConversion(isString(), "value is not a string");
    return std::get<std::string>(data);
}

std::string& Value::asString() {
    assertConversion(isString(), "value is not a string");
    return std::get<std::string>(data);
}

const Array& Value::asArray() const {
    assertConversion(isArray(), "value is not an array");
    return std::get<Array>(data);
}

Array& Value::asArray() {
    assertConversion(isArray(), "value is not an array");
    return std::get<Array>(data);
}

const Object& Value::asObject() const {
    assertConversion(isObject(), "value is not an object");
    return std::get<Object>(data);
}

Object& Value::asObject() {
    assertConversion(isObject(), "value is not an object");
    return std::get<Object>(data);
}

void Value::clear() {
    data.emplace<std::monostate>();
}

void Value::assertConversion(bool isValid, const char* msg) const {
    if (!isValid) {
        throw ConversionException(msg);
    }
}

}