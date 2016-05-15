/**
 * @file src/program/game/item/item_Coin.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "item_Coin.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Coin::Coin(Type t, Size s, int am, sf::Vector2i pos) {
        amount_    = am;
        type_      = t;
        size_      = s;
        equipable_  = false;
        disposable_ = false;
        stackable_  = true;
        ID_        = 3*size_ + type_ + 1;
        iconIndex_ = type_ + (size_+2)*16 + 1;

        if (type_ == BRONZE) name_ = resources.dictionary["item.coin.bronze"]; else
        if (type_ == SILVER) name_ = resources.dictionary["item.coin.silver"]; else
        if (type_ == GOLDEN) name_ = resources.dictionary["item.coin.gold"];

        body_.resize(4);
        body_.setPrimitiveType(sf::Quads);

        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        int tu = iconIndex_%16;
        int tv = iconIndex_/16;

        body_[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body_[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body_[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body_[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);
    }

    Coin::~Coin() {}

    void Coin::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

}
