#include "Value/Object.hpp"

#include "Value/Value.hpp"

namespace ezio {

static const Value EMPTY_VALUE;

const Value& Object::operator[](std::string_view name) const {
	if (auto it = members.find(name); it != members.end()) {
		return it->second;
	}

	return EMPTY_VALUE;
}

Value& Object::operator[](std::string_view name) {
	if (auto it = members.find(name); it != members.end()) {
		return it->second;
	}

	auto [it, _] = members.emplace(name, Value{});
	return it->second;
}

bool Object::hasMember(std::string_view name) const {
	return members.find(name) != members.end();
}

void Object::addMember(std::string_view name, const Value& value) { 
	auto [it, inserted] = members.emplace(name, value);
	if (!inserted) {
		it->second = value;
	}
}

void Object::addMember(std::string_view name, Value&& value) {
	auto [it, inserted] = members.emplace(name, std::move(value));
	if (!inserted) {
		it->second = std::move(value);
	}
}

void Object::removeMember(std::string_view name) {
	if (auto it = members.find(name); it != members.end()) {
		members.erase(it);
	}
}

}