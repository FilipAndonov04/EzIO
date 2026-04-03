#pragma once
#include <EzIO/Value/Value.h>

#include <unordered_map>
#include <string>

namespace EzIO {

class Object : public Value {
public:
	Object() = default;
	Object(std::unordered_map<std::string, std::unique_ptr<Value>>&& members);

	static ValueType getStaticType();

	ValueType getType() const override;
	std::unique_ptr<Value> clone() const override;

	void acceptSerializer(Serializer& serializer) const override;

	const std::unordered_map<std::string, std::unique_ptr<Value>>& getMembers() const;
	std::unordered_map<std::string, std::unique_ptr<Value>>& getMembers();

	const Value& getMember(const std::string& name) const;
	Value& getMember(const std::string& name);
	const Value& operator[](const std::string& name) const;
	Value& operator[](const std::string& name);
	void setMember(const std::string& name, std::unique_ptr<Value>&& value);

	bool hasMember(const std::string& name) const;
	void addMember(const std::string& name, std::unique_ptr<Value>&& value);
	void removeMember(const std::string& name);

private:
	void assertHasMember(const std::string& name) const;
	void assertDoesNotHaveMember(const std::string& name) const;

	std::unordered_map<std::string, std::unique_ptr<Value>> members;
};

}