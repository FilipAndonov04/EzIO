#pragma once
#include "EzIO/Value/Value.h"

namespace EzIO {

class Null : public Value {
public:
	static ValueType getStaticType();
	static std::unique_ptr<Null> of();

	ValueType getType() const override;
	std::unique_ptr<Value> clone() const override;

	void acceptSerializer(Serializer& serializer) const override;
};

}