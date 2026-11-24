#include "Deck.hpp"

ezio::Value Card::serialize() const {
    ezio::Object o;
    o.addMember("suit", suit == Suit::Black ? std::string("black") : std::string("red"));
    o.addMember("rank", double(rank));
    return o;
}

void Card::deserialize(const ezio::Value& value) {
    const ezio::Object& o = value.asObjectOrDefault();
    suit = o["suit"].asStringOrDefault() == "black" ? Suit::Black : Suit::Red;
    rank = o["rank"].asNumberOrDefault();
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
    const ezio::Object* obj = value.asObject();
    if (obj == nullptr) {
        return;
    }

    const ezio::Array* arr = (*obj)["cards"].asArray();
    if (arr == nullptr) {
        return;
    }

    cards.clear();
    cards.resize(arr->size());
    size_t i = 0;
    for (auto& el : *arr) {
        cards[i++].deserialize(el);
    }
}
