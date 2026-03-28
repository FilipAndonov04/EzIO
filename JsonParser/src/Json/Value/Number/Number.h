#pragma once
#include "Json/Value/Value.h"

namespace Json {

class Number : public Value {
public:
	Number();
	explicit Number(double data);

	ValueType getType() const override;

	double getData() const;
	void setData(double data);

private:
	double data;
};

}