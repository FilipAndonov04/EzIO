#include "Value/Value.hpp"

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

void Value::clear() noexcept {
    data.emplace<std::monostate>();
}

bool Value::isNull() const noexcept {
    return holds_alternative<std::monostate>(data);
}

bool Value::isNumber() const noexcept {
    return std::holds_alternative<double>(data);
}

bool Value::isBoolean() const noexcept {
    return std::holds_alternative<bool>(data);
}

bool Value::isString() const noexcept {
    return std::holds_alternative<std::string>(data);
}

bool Value::isArray() const noexcept {
    return std::holds_alternative<Array>(data);
}

bool Value::isObject() const noexcept {
    return std::holds_alternative<Object>(data);
}

const double* Value::asNumber() const noexcept {
    return std::get_if<double>(&data);
}

double* Value::asNumber() noexcept {
    return std::get_if<double>(&data);
}

const bool* Value::asBoolean() const noexcept {
    return std::get_if<bool>(&data);
}

bool* Value::asBoolean() noexcept {
    return std::get_if<bool>(&data);

}

const std::string* Value::asString() const noexcept {
    return std::get_if<std::string>(&data);
}

std::string* Value::asString() noexcept {
    return std::get_if<std::string>(&data);
}

const Array* Value::asArray() const noexcept {
    return std::get_if<Array>(&data);
}

Array* Value::asArray() noexcept {
    return std::get_if<Array>(&data);
}

const Object* Value::asObject() const noexcept {
    return std::get_if<Object>(&data);
}

Object* Value::asObject() noexcept {
    return std::get_if<Object>(&data);
}

double Value::asNumberOrDefault() const noexcept {
    if (const double* num = asNumber()) {
        return *num;
    }

    return 0.0;
}

bool Value::asBooleanOrDefault() const noexcept {
    if (const bool* b = asBoolean()) {
        return *b;
    }

    return false;
}

static const std::string EMPTY_STRING;

const std::string& Value::asStringOrDefault() const noexcept {
    if (const std::string* str = asString()) {
        return *str;
    }

    return EMPTY_STRING;
}

static const Array EMPTY_ARRAY;

const Array& Value::asArrayOrDefault() const noexcept {
    if (const Array* arr = asArray()) {
        return *arr;
    }

    return EMPTY_ARRAY;
}

static const Object EMPTY_OBJECT;

const Object& Value::asObjectOrDefault() const noexcept {
    if (const Object* obj = asObject()) {
        return *obj;
    }

    return EMPTY_OBJECT;
}

}