#include "Deck.h"

ezio::Value Card::serialize() const {
    ezio::Object o;
    o.addMember("suit", suit == Suit::Black ? std::string("black") : std::string("red"));
    o.addMember("rank", double(rank));
    return o;
}

void Card::deserialize(const ezio::Value& value) {
    const ezio::Object& o = value.asObject();
    suit = o["suit"].asString() == "black" ? Suit::Black : Suit::Red;
    rank = o["rank"].asNumber();
}

ezio::Value Deck::serialize() const {
    ezio::Array arr;
    for (auto& c : cards) {
        arr.pushBack(c.serialize());
    }

    ezio::Object o;
    o.addMember("cards", arr);
    return o;
}

void Deck::deserialize(const ezio::Value& value) {
    const ezio::Object& o = value.asObject();
    ezio::Array arr = o["cards"].asArray();

    cards.clear();
    cards.resize(arr.getSize());
    size_t i = 0;
    for (auto& el : arr) {
        cards[i++].deserialize(el);
    }
}
