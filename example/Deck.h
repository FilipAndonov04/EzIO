#pragma once

#include <vector>

#include "EzIO/EzIO.h"

enum class Suit {
	Black,
	Red
};

struct Card {
	Suit suit;
	unsigned rank;

	ezio::Value serialize() const;
	void deserialize(const ezio::Value& value);
};

struct Deck {
	std::vector<Card> cards;

	ezio::Value serialize() const;
	void deserialize(const ezio::Value& value);
};