#pragma once
#include "EzIO/Value/Value.h"
#include "EzIO/Exception/Value/ValueConversionException.h"

namespace EzIO {

template <typename T>
const T& valueAs(const Value& value);

template <typename T>
T& valueAs(Value& value);

template <typename T>
const T* valueAsNoThrow(const Value& value);

template <typename T>
T* valueAsNoThrow(Value& value);

template<typename T>
const T& valueAs(const Value& value) {
	if (value.getType() != T::getStaticType()) {
		throw ValueConversionException("invalid value conversion");
	}

	return static_cast<const T&>(value);
}

template<typename T>
T& valueAs(Value& value) {
	if (value.getType() != T::getStaticType()) {
		throw ValueConversionException("invalid value conversion");
	}

	return static_cast<T&>(value);
}

template<typename T>
const T* valueAsNoThrow(const Value& value) {
	if (value.getType() != T::getStaticType()) {
		return nullptr;
	}

	return static_cast<const T&>(value);
}

template<typename T>
T* valueAsNoThrow(Value& value) {
	if (value.getType() != T::getStaticType()) {
		return nullptr;
	}

	return static_cast<T&>(value);
}

}