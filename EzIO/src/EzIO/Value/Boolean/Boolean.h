#pragma once
#include "EzIO/Value/Value.h"

namespace EzIO {

class Boolean : public Value {
public:
	explicit Boolean(bool data);

	static ValueType getStaticType();
	static std::unique_ptr<Boolean> of(bool data);

	ValueType getType() const override;
	std::unique_ptr<Value> clone() const override;

	void acceptSerializer(Serializer& serializer) const override;
	
	bool getData() const;
	void setData(bool data);

private:
	bool data;
};

}