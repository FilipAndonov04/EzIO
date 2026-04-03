#include "Object.h"
#include "EzIO/IO/Serializer/Serializer.h"
#include "EzIO/IO/Deserializer/Deserializer.h"
#include "EzIO/Exception/Value/ValueException.h"

namespace EzIO {

Object::Object(std::unordered_map<std::string, std::unique_ptr<Value>>&& members) 
	: members(std::move(members)) {}

ValueType Object::getStaticType() {
	return ValueType::Object;
}

ValueType Object::getType() const {
	return getStaticType();
}

std::unique_ptr<Value> Object::clone() const {
	std::unordered_map<std::string, std::unique_ptr<Value>> copies;
	copies.reserve(members.size());

	for (const auto& member : members) {
		copies.insert(std::make_pair(member.first, member.second->clone()));
	}

	return std::make_unique<Object>(std::move(copies));
}

void Object::acceptSerializer(Serializer& serializer) const {
	serializer.serialize(*this);
}

const std::unordered_map<std::string, std::unique_ptr<Value>>& Object::getMembers() const {
	return members;
}

std::unordered_map<std::string, std::unique_ptr<Value>>& Object::getMembers() {
	return members;
}

const Value& Object::getMember(const std::string& name) const {
	assertHasMember(name);

	return *members.at(name);
}

Value& Object::getMember(const std::string& name) {
	assertHasMember(name);

	return *members.at(name);
}

const Value& Object::operator[](const std::string& name) const {
	return getMember(name);
}

Value& Object::operator[](const std::string& name) {
	return getMember(name);
}

void Object::setMember(const std::string& name, std::unique_ptr<Value>&& value) {
	members[name] = std::move(value);
}

bool Object::hasMember(const std::string& name) const {
	return members.find(name) != members.end();
}

void Object::addMember(const std::string& name, std::unique_ptr<Value>&& value) {
	assertDoesNotHaveMember(name);

	members.insert(std::make_pair(name, std::move(value)));
}

void Object::removeMember(const std::string& name) {
	assertHasMember(name);

	members.erase(name);
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