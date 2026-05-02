#include <EzIO/EzIO.h>
#include "Deck.h"

#include <iostream>
#include <fstream>

struct Point {
	char name[20];
	float x, y;
};

struct Points {
	std::vector<Point> data;
};

EzIO::Object toObject(Point p) {
	EzIO::Object o;
	o.addMember("name", std::string(p.name));
	o.addMember("x", double(p.x));
	o.addMember("y", double(p.y));
	return o;
}

void fromObject(const EzIO::Object& o, Point& p) {
	strncpy_s(p.name, o["name"].asString().c_str(), 100);
	p.x = o["x"].asNumber();
	p.y = o["y"].asNumber();
}

EzIO::Object toObject(const Points& points) {
	EzIO::Array arr(points.data.size());
	for (auto& p : points.data) {
		arr.pushBack(toObject(p));
	}

	EzIO::Object o;
	o.addMember("points", std::move(arr));
	return o;
}

void fromObject(const EzIO::Object& o, Points& points) {
	auto& arr = o["points"].asArray();
	for (const auto& el : arr) {
		Point p;
		fromObject(el.asObject(), p);
		points.data.push_back(p);
	}
}

int main() {
	Deck deck{
		{
			Card{Suit::Red, 8},
			Card{Suit::Black, 4},
			Card{Suit::Red, 2}
		}
	};

	std::ofstream ofs("file2.txt");
	EzIO::JsonSerializer s(ofs);
	auto o = deck.serialize();
	s.serialize(o);
	ofs.close();

	try {
		std::ifstream ifs("file2.txt");
		EzIO::JsonDeserializer d(ifs);
		auto val = d.deserialize();
		s.setOutputStream(std::cout);
		s.serialize(val);
		deck.deserialize(val);
		auto x = deck.serialize();
		s.serialize(x);
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}