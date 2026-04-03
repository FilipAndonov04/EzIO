#include "Null.h"
#include "EzIO/IO/Serializer/Serializer.h"
#include "EzIO/IO/Deserializer/Deserializer.h"

namespace EzIO {

ValueType Null::getStaticType() {
    return ValueType::Null;
}

std::unique_ptr<Null> Null::of() {
    return std::make_unique<Null>();
}

ValueType Null::getType() const {
    return getStaticType();
}

std::unique_ptr<Value> Null::clone() const {
    return of();
}

void Null::acceptSerializer(Serializer& serializer) const {
    serializer.serialize(*this);
}

}