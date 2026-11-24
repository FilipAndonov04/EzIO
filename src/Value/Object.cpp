#include "Value/Object.hpp"

#include "Value/Value.hpp"

namespace ezio {

static const Value EMPTY_VALUE;

const Value& Object::operator[](const std::string& name) const {
	if (auto it = members.find(name); it != members.end()) {
		return it->second;
	}

	return members.at(name);
}

Value& Object::operator[](const std::string& name) {
	return members[name];
}

bool Object::hasMember(const std::string& name) const {
	return members.find(name) != members.end();
}

void Object::addMember(const std::string& name, const Value& value) { 
	members[name] = value;
}

void Object::addMember(const std::string& name, Value&& value) {
	members[name] = std::move(value);
}

void Object::removeMember(const std::string& name) {
	members.erase(name);
}

}