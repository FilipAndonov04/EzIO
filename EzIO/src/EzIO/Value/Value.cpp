#include "Value.h"
#include "EzIO/Value/Array/Array.h"
#include "EzIO/Value/Object/Object.h"
#include "EzIO/Exception/Value/ConversionException.h"

namespace ezio {

Value::Value(double number)
    : number(new double(number)) {}

Value::Value(bool boolean) 
    : boolean(new bool(boolean)) {}

Value::Value(std::string string) 
    : string(new std::string(std::move(string))) {}

Value::Value(Array array) 
    : array(new Array(std::move(array))) {}

Value::Value(Object object) 
    : object(new Object(std::move(object))) {}

Value::Value(const Value& other) {
    copyFrom(other);
}

Value::Value(Value& other) {
    copyFrom(other);
}

Value::Value(Value&& other) noexcept {
    moveFrom(std::move(other));
}

Value& Value::operator=(double number) {
    clear();
    this->number = new double(number);

    return *this;
}

Value& Value::operator=(bool boolean) {
    clear();
    this->boolean = new bool(boolean);

    return *this;
}

Value& Value::operator=(std::string string) {
    clear();
    this->string = new std::string(std::move(string));

    return *this;
}

Value& Value::operator=(Array array) {
    clear();
    this->array = new Array(std::move(array));

    return *this;
}

Value& Value::operator=(Object object) {
    clear();
    this->object = new Object(std::move(object));

    return *this;
}

Value& Value::operator=(const Value& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

Value& Value::operator=(Value& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

Value& Value::operator=(Value&& other) noexcept {
    if (this != &other) {
        clear();
        moveFrom(std::move(other));
    }
    return *this;
}

Value::~Value() {
    clear();
}

bool Value::isNull() const {
    return !isNumber() && !isBoolean() && !isString() && 
        !isArray() && !isObject();
}

bool Value::isNumber() const {
    return number;
}

bool Value::isBoolean() const {
    return boolean;
}

bool Value::isString() const {
    return string;
}

bool Value::isArray() const {
    return array;
}

bool Value::isObject() const {
    return object;
}

double Value::asNumber() const {
    assertConversion(isNumber(), "value is not a number");
    return *number;
}

double& Value::asNumber() {
    assertConversion(isNumber(), "value is not a number");
    return *number;
}

bool Value::asBoolean() const {
    assertConversion(isBoolean(), "value is not a boolean");
    return *boolean;
}

bool& Value::asBoolean() {
    assertConversion(isBoolean(), "value is not a boolean");
    return *boolean;
}

const std::string& Value::asString() const {
    assertConversion(isString(), "value is not a string");
    return *string;
}

std::string& Value::asString() {
    assertConversion(isString(), "value is not a string");
    return *string;
}

const Array& Value::asArray() const {
    assertConversion(isArray(), "value is not an array");
    return *array;
}

Array& Value::asArray() {
    assertConversion(isArray(), "value is not an array");
    return *array;
}

const Object& Value::asObject() const {
    assertConversion(isObject(), "value is not an object");
    return *object;
}

Object& Value::asObject() {
    assertConversion(isObject(), "value is not an object");
    return *object;
}

void Value::clear() {
    if (number) {
        delete number;
    } else if (boolean) {
        delete boolean;
    } else if (string) {
        delete string;
    } else if (array) {
        delete array;
    } else if (object) {
        delete object;
    }

    number = nullptr;
    boolean = nullptr;
    string = nullptr;
    array = nullptr;
    object = nullptr;
}

void Value::assertConversion(bool isValid, const char* msg) const {
    if (!isValid) {
        throw ConversionException(msg);
    }
}

void Value::copyFrom(const Value& other) {
    if (other.number) {
        number = new double(*other.number);
    } else if (other.boolean) {
        boolean = new bool(*other.boolean);
    } else if (other.string) {
        string = new std::string(*other.string);
    } else if (other.array) {
        array = new Array(*other.array);
    } else if (other.object) {
        object = new Object(*other.object);
    }
}

void Value::moveFrom(Value&& other) noexcept {
    number = other.number;
    boolean = other.boolean;
    string = other.string;
    array = other.array;
    object = other.object;

    other.number = nullptr;
    other.boolean = nullptr;
    other.string = nullptr;
    other.array = nullptr;
    other.object = nullptr;
}

}