#include "Number.h"
#include "EzIO/IO/Serializer/Serializer.h"
#include "EzIO/IO/Deserializer/Deserializer.h"

namespace EzIO {

Number::Number(double data) 
    : data(data) {}

ValueType Number::getStaticType() {
    return ValueType::Number;
}

std::unique_ptr<Number> Number::of(double data) {
    return std::make_unique<Number>(data);
}

ValueType Number::getType() const {
    return getStaticType();
}

std::unique_ptr<Value> Number::clone() const {
    return of(data);
}

void Number::acceptSerializer(Serializer& serializer) const {
    serializer.serialize(*this);
}

double Number::getData() const {
    return data;
}

void Number::setData(double data) {
    this->data = data;
}

}