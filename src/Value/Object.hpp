#pragma once

#include <string>
#include <string_view>
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

	const Value& operator[](std::string_view name) const;
	Value& operator[](std::string_view name);

	bool hasMember(std::string_view name) const;
	void addMember(std::string_view name, const Value& value);
	void addMember(std::string_view name, Value&& value);
	void removeMember(std::string_view name);

private:
	struct StringHash {
		using is_transparent = void;

		std::size_t operator()(std::string_view s) const noexcept {
			return std::hash<std::string_view>{}(s);
		}
	};

	struct StringEqual {
		using is_transparent = void;

		bool operator()(std::string_view a, std::string_view b) const noexcept {
			return a == b;
		}
	};

private:
	std::unordered_map<std::string, Value, StringHash, StringEqual> members;
};

}