#include <iostream>
#include <fstream>

#include <EzIO.hpp>

#include "Deck.hpp"

struct Point {
	char name[20];
	float x, y;
};

struct Points {
	std::vector<Point> data;
};

ezio::Object toObject(Point p) {
	ezio::Object o;
	o.addMember("name", std::string(p.name));
	o.addMember("x", double(p.x));
	o.addMember("y", double(p.y));
	return o;
}

void fromObject(const ezio::Object& o, Point& p) {
	strncpy_s(p.name, o["name"].asStringOrDefault().c_str(), 100);
	p.x = o["x"].asNumberOrDefault();
	p.y = o["y"].asNumberOrDefault();
}

ezio::Object toObject(const Points& points) {
	ezio::Array arr(points.data.size());
	for (auto& p : points.data) {
		arr.pushBack(toObject(p));
	}

	ezio::Object o;
	o.addMember("points", std::move(arr));
	return o;
}

void fromObject(const ezio::Object& o, Points& points) {
	auto& arr = o["points"].asArrayOrDefault();
	for (const auto& el : arr) {
		Point p;
		fromObject(el.asObjectOrDefault(), p);
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

	std::ofstream ofs(RESOURCE_PATH "file2.json");

	auto o = deck.serialize();
	ezio::serializeJson(ofs, o);

	ofs.close();

	try {
		std::ifstream ifs(RESOURCE_PATH "file2.json");

		auto val = ezio::deserializeJson(ifs);
		ezio::serializeJson(std::cout, val);

		std::cout << '\n';

		deck.deserialize(val);
		auto x = deck.serialize();
		ezio::serializeJson(std::cout, x);
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}