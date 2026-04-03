#include "Object.h"
#include "EzIO/IO/Serializer/Serializer.h"
#include "EzIO/IO/Deserializer/Deserializer.h"
#include "EzIO/Exception/Value/ValueException.h"

namespace EzIO {

Object::Object(size_t initialMembersCapacity) {
	members.reserve(initialMembersCapacity);
}

size_t Object::getMembersCount() const {
	return members.size();
}

void Object::clear() {
	members.clear();
}

const Value& Object::operator[](const std::string& name) const {
	assertHasMember(name);
	return members.at(name);
}

Value& Object::operator[](const std::string& name) {
	assertHasMember(name);
	return members.at(name);
}

bool Object::hasMember(const std::string& name) const {
	return members.find(name) != members.end();
}

void Object::addMember(const std::string& name, const Value& value) { 
	assertDoesNotHaveMember(name);
	members.insert(std::make_pair(name, value));
}

void Object::addMember(const std::string& name, Value&& value) {
	assertDoesNotHaveMember(name);
	members.insert(std::make_pair(name, std::move(value)));
}

void Object::removeMember(const std::string& name) {
	assertHasMember(name);
	members.erase(name);
}

std::unordered_map<std::string, Value>::const_iterator Object::cbegin() const {
	return members.cbegin();
}

std::unordered_map<std::string, Value>::const_iterator Object::cend() const {
	return members.cend();
}

std::unordered_map<std::string, Value>::const_iterator Object::begin() const {
	return members.begin();
}

std::unordered_map<std::string, Value>::const_iterator Object::end() const {
	return members.end();
}

std::unordered_map<std::string, Value>::iterator Object::begin() {
	return members.begin();
}

std::unordered_map<std::string, Value>::iterator Object::end() {
	return members.end();
}

void Object::assertHasMember(const std::string& name) const {
	if (!hasMember(name)) {
		throw ValueException("member does not exist");
	}
}

void Object::assertDoesNotHaveMember(const std::string& name) const {
	if (hasMember(name)) {
		throw ValueException("member exists");
	}
}

}