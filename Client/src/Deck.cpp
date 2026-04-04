#include "Deck.h"

EzIO::Value Card::serialize() const {
    EzIO::Object o;
    o.addMember("suit", suit == Suit::Blue ? std::string("blue") : suit == Suit::Black ? std::string("black") : std::string("red"));
    o.addMember("rank", double(rank));
    return o;
}

void Card::deserialize(const EzIO::Value& value) {
    EzIO::Object o = value.asObject();
    suit = o["suit"].asString() == "black" ? Suit::Black : o["suit"].asString() == "blue" ? Suit::Blue : Suit::Red;
    rank = o["rank"].asNumber();
}

EzIO::Value Deck::serialize() const {
    EzIO::Array arr;
    for (auto& c : cards) {
        arr.pushBack(c.serialize());
    }

    EzIO::Object o;
    o.addMember("cards", arr);
    return o;
}

void Deck::deserialize(const EzIO::Value& value) {
    EzIO::Object o = value.asObject();
    EzIO::Array arr = o["cards"].asArray();

    cards.clear();
    cards.resize(arr.getSize());
    int i = 0;
    for (auto& el : arr) {
        cards[i++].deserialize(el);
    }
}
