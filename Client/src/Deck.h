#pragma once
#include "EzIO/EzIO.h"

#include <vector>

enum class Suit {
	Black,
	Red,
	Blue
};

struct Card {
	Suit suit;
	unsigned rank;

	EzIO::Value serialize() const;
	void deserialize(const EzIO::Value& value);
};

struct Deck {
	std::vector<Card> cards;

	EzIO::Value serialize() const;
	void deserialize(const EzIO::Value& value);
};