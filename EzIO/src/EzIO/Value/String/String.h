#pragma once
#include "EzIO/Value/Value.h"

#include <string>

namespace EzIO {

class String : public Value {
public:
	explicit String(std::string data);

	static ValueType getStaticType();
	static std::unique_ptr<String> of(std::string data);

	ValueType getType() const override;
	std::unique_ptr<Value> clone() const override;

	void acceptSerializer(Serializer& serializer) const override;

	const std::string& getData() const;
	std::string& getData();
	void setData(std::string data);

private:
	std::string data;
};

}