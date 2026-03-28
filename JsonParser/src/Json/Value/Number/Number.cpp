#include "Number.h"

namespace Json {

Number::Number() 
    : Number(0.0) {}

Number::Number(double data) 
    : data(data) {}

ValueType Json::Number::getType() const {
    return ValueType::Number;
}

double Number::getData() const {
    return data;
}

void Number::setData(double data) {
    this->data = data;
}

}