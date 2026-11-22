#pragma once

#include <string>
#include <unordered_map>

namespace ezio {

class Value;

class Object {
public:
	using Iterator = std::unordered_map<std::string, Value>::iterator;
	using ConstIterator = std::unordered_map<std::string, Value>::const_iterator;

public:
	Object() = default;
	explicit Object(size_t initialCapacity) { members.reserve(initialCapacity); }

	Iterator begin() noexcept { return members.begin(); }
	Iterator end() noexcept { return members.end(); }
	ConstIterator begin() const noexcept { return members.begin(); }
	ConstIterator end() const noexcept { return members.end(); }
	ConstIterator cbegin() const noexcept { return members.cbegin(); }
	ConstIterator cend() const noexcept { return members.cend(); }

	size_t size() const noexcept { return members.size(); }
	bool isEmpty() const noexcept { return members.empty(); }

	void clear() noexcept { members.clear(); }

	const Value& operator[](const std::string& name) const;
	Value& operator[](const std::string& name);

	bool hasMember(const std::string& name) const;
	void addMember(const std::string& name, const Value& value);
	void addMember(const std::string& name, Value&& value);
	void removeMember(const std::string& name);

private:
	std::unordered_map<std::string, Value> members;
};

}