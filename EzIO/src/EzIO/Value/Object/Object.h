#pragma once
#include "EzIO/Value/Value.h"

#include <string>
#include <unordered_map>

namespace EzIO {

class Object {
public:
	Object() = default;
	Object(size_t initialMembersCapacity);

	size_t getMembersCount() const;
	void clear();

	const Value& operator[](const std::string& name) const;
	Value& operator[](const std::string& name);

	bool hasMember(const std::string& name) const;
	void addMember(const std::string& name, const Value& value);
	void addMember(const std::string& name, Value&& value);
	void removeMember(const std::string& name);

	std::unordered_map<std::string, Value>::const_iterator cbegin() const;
	std::unordered_map<std::string, Value>::const_iterator cend() const;
	std::unordered_map<std::string, Value>::const_iterator begin() const;
	std::unordered_map<std::string, Value>::const_iterator end() const;
	std::unordered_map<std::string, Value>::iterator begin();
	std::unordered_map<std::string, Value>::iterator end();

private:
	void assertHasMember(const std::string& name) const;
	void assertDoesNotHaveMember(const std::string& name) const;

	std::unordered_map<std::string, Value> members;
};

}