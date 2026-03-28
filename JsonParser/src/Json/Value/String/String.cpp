#include "String.h"

namespace Json {

String::String(std::string data) 
    : data(std::move(data)) {}

ValueType String::getType() const {
    return ValueType::String;
}

const std::string& String::getData() const {
    return data;
}

std::string& String::getData() {
    return data;
}

void String::setData(std::string data) {
    this->data = std::move(data);
}

}