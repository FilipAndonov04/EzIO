#include "Object.h"

#include "EzIO/Value/Value.h"
#include "EzIO/IO/Serializer/Serializer.h"
#include "EzIO/IO/Deserializer/Deserializer.h"
#include "EzIO/Exception/Exception.h"

namespace ezio {

Object::Object(size_t initialMembersCapacity) {
	members.reserve(initialMembersCapacity);
}

size_t Object::getMemberCount() const {
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

Object::ConstIterator Object::cbegin() const {
	return members.cbegin();
}

Object::ConstIterator Object::cend() const {
	return members.cend();
}

Object::ConstIterator Object::begin() const {
	return members.begin();
}

Object::ConstIterator Object::end() const {
	return members.end();
}

Object::Iterator Object::begin() {
	return members.begin();
}

Object::Iterator Object::end() {
	return members.end();
}

void Object::assertHasMember(const std::string& name) const {
	if (!hasMember(name)) {
		throw Exception("member does not exist");
	}
}

void Object::assertDoesNotHaveMember(const std::string& name) const {
	if (hasMember(name)) {
		throw Exception("member exists");
	}
}

}