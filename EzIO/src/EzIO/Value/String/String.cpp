#include "String.h"
#include "EzIO/IO/Serializer/Serializer.h"
#include "EzIO/IO/Deserializer/Deserializer.h"

namespace EzIO {

String::String(std::string data) 
    : data(std::move(data)) {}

ValueType String::getStaticType() {
    return ValueType::String;
}

std::unique_ptr<String> String::of(std::string data) {
    return std::make_unique<String>(std::move(data));
}

ValueType String::getType() const {
    return getStaticType();
}

std::unique_ptr<Value> String::clone() const {
    return of(data);
}

void String::acceptSerializer(Serializer& serializer) const {
    serializer.serialize(*this);
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