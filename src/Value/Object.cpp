#include "Value/Object.hpp"

#include "Value/Value.hpp"

namespace ezio {

Object::Object(size_t initialMembersCapacity) {
	members.reserve(initialMembersCapacity);
}

Object::Iterator Object::begin() {
	return members.begin();
}

Object::Iterator Object::end() {
	return members.end();
}

Object::ConstIterator Object::begin() const {
	return members.begin();
}

Object::ConstIterator Object::end() const {
	return members.end();
}

Object::ConstIterator Object::cbegin() const {
	return members.cbegin();
}

Object::ConstIterator Object::cend() const {
	return members.cend();
}

size_t Object::getMemberCount() const {
	return members.size();
}

void Object::clear() {
	members.clear();
}

const Value& Object::operator[](const std::string& name) const {
	return members.at(name);
}

Value& Object::operator[](const std::string& name) {
	return members.at(name);
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