#include "EzIO/IO/Serializer/Json/JsonSerializer.h"
#include "EzIO/IO/Deserializer/Json/JsonDeserializer.h"
#include "EzIO/Value/Value.h"
#include "EzIO/Value/Array/Array.h"
#include "EzIO/Value/Object/Object.h"

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

Object toObject(Point p) {
	Object o;
	o.addMember("name", std::string(p.name));
	o.addMember("x", p.x);
	o.addMember("y", p.y);
	return o;
}

void fromObject(const Object& o, Point& p) {
	strncpy_s(p.name, o["name"].asString().c_str(), 100);
	p.x = o["x"].asNumber();
	p.y = o["y"].asNumber();
}

Object toObject(const Points& points) {
	Array arr(points.data.size());
	for (auto& p : points.data) {
		arr.pushBack(toObject(p));
	}

	Object o;
	o.addMember("points", std::move(arr));
	return o;
}

void fromObject(const Object& o, Points& points) {
	auto& arr = o["points"].asArray();
	for (const auto& el : arr) {
		Point p;
		fromObject(el.asObject(), p);
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
	s.serialize(o);
	ofs.close();

	try {
		std::ifstream ifs("file.txt");
		JsonDeserializer d(ifs);
		auto val = d.deserialize();
		s.setOutputStream(std::cout);
		s.serialize(val);
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}