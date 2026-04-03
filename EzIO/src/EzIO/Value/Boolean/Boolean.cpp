#include "Boolean.h"
#include "EzIO/IO/Serializer/Serializer.h"
#include "EzIO/IO/Deserializer/Deserializer.h"

namespace EzIO {

Boolean::Boolean(bool data) 
    : data(data) {}

ValueType Boolean::getStaticType() {
    return ValueType::Boolean;
}

std::unique_ptr<Boolean> Boolean::of(bool data) {
    return std::make_unique<Boolean>(data);
}

ValueType Boolean::getType() const {
    return getStaticType();
}

std::unique_ptr<Value> Boolean::clone() const {
    return of(data);
}

void Boolean::acceptSerializer(Serializer& serializer) const {
    serializer.serialize(*this);
}

bool Boolean::getData() const {
    return data;
}

void Boolean::setData(bool data) {
    this->data = data;
}

}