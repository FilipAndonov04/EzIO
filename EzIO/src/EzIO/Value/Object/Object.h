#pragma once
#include "EzIO/Value/Value.h"

#include <string>
#include <unordered_map>

namespace EzIO {

class Object {
public:
	using Iterator = std::unordered_map<std::string, Value>::iterator;
	using ConstIterator = std::unordered_map<std::string, Value>::const_iterator;

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

	ConstIterator cbegin() const;
	ConstIterator cend() const;
	ConstIterator begin() const;
	ConstIterator end() const;
	Iterator begin();
	Iterator end();

private:
	void assertHasMember(const std::string& name) const;
	void assertDoesNotHaveMember(const std::string& name) const;

	std::unordered_map<std::string, Value> members;
};

}