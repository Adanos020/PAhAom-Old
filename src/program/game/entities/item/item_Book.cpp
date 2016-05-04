/**
 * @file src/program/game/item/item_Book.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "item_Book.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;
extern sf::Color potionColors[9];

namespace rr {

    Book::Book(Type type, int am, sf::Vector2i pos) {
        type_       = type;
        amount_     = am;
        ID_         = type_+10;
        discovered_ = false;
        disposable_ = true;

        body_.resize(4);
        body_.setPrimitiveType(sf::Quads);

        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        int tu = 0;
        int tv = 1;

        body_[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body_[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body_[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body_[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);

        for (int i=0; i<4; i++) {
            body_[i].color = potionColors[type_];
        }
    }

    Book::~Book() {}

    void Book::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void Book::update() {}

    void Book::reveal() {
        discovered_ = true;
    }

}
