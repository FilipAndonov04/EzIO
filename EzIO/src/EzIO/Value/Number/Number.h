#pragma once
#include "EzIO/Value/Value.h"

namespace EzIO {

class Number : public Value {
public:
	explicit Number(double data);

	static ValueType getStaticType();
	static std::unique_ptr<Number> of(double data);

	ValueType getType() const override;
	std::unique_ptr<Value> clone() const override;

	void acceptSerializer(Serializer& serializer) const override;

	double getData() const;
	void setData(double data);

private:
	double data;
};

}