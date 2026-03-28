#pragma once
#include "Json/Value/Value.h"

#include <string>

namespace Json {

class String : public Value {
public:
	String() = default;
	String(std::string data);

	ValueType getType() const override;

	const std::string& getData() const;
	std::string& getData();
	void setData(std::string data);

private:
	std::string data;
}

}