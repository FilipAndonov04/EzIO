#include "Json/JsonWriter.h"

#include <iostream>

int main() {
	int x;
	std::cin >> x;

	Json::JsonWriter writer;
	writer.writeNumber(std::cout, x);
}