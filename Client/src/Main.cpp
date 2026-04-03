#include "EzIO/IO/Serializer/Json/JsonSerializer.h"
#include "EzIO/IO/Deserializer/Json/JsonDeserializer.h"
#include "EzIO/Value/Value.h"
#include "EzIO/Value/Number/Number.h"
#include "EzIO/Value/String/String.h"
#include "EzIO/Value/Boolean/Boolean.h"
#include "EzIO/Value/Array/Array.h"
#include "EzIO/Value/Object/Object.h"
#include "EzIO/Value/Null/Null.h"
#include "EzIO/Value/ValueConversion.hpp"

#include <iostream>
#include <fstream>

using namespace EzIO;

struct Point {
	char name[20];
	float x, y;
};

struct Points {
	std::vector<Point> data;
};

auto toObject(Point p) {
	auto o = std::make_unique<Object>();
	o->addMember("name", String::of(p.name));
	o->addMember("x", Number::of(p.x));
	o->addMember("y", Number::of(p.y));
	return o;
}

void fromObject(const Object& o, Point& p) {
	strncpy_s(p.name, valueAs<String>(o["name"]).getData().c_str(), 100);
	p.x = valueAs<Number>(o["x"]).getData();
	p.y = valueAs<Number>(o["y"]).getData();
}

auto toObject(const Points& points) {
	auto arr = std::make_unique<Array>();
	for (auto& p : points.data) {
		arr->pushBack(toObject(p));
	}

	auto o = std::make_unique<Object>();
	o->addMember("points", std::move(arr));
	return o;
}

void fromObject(const Object& o, Points& points) {
	auto& arr = valueAs<Array>(o["points"]);
	for (auto& el : arr.getElements()) {
		Point p;
		fromObject(valueAs<Object>(*el), p);
		points.data.push_back(p);
	}
}

int main() {
	size_t size;
	std::cin >> size;

	Points points;
	while (size-- > 0) {
		Point p;
		std::cin >> p.name >> p.x >> p.y;
		points.data.push_back(p);
	}

	std::ofstream ofs("file.txt");
	JsonSerializer s(ofs);
	auto o = toObject(points);
	s.serialize(*o);
	ofs.close();

	try {
		std::ifstream ifs("file.txt");
		JsonDeserializer d(ifs);
		auto val = d.deserialize();
		s.setOutputStream(std::cout);
		val->acceptSerializer(s);
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}