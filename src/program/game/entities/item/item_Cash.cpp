/**
 * @file src/program/game/item/item_Cash.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "item_Cash.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Cash::Cash(Type t, int am, sf::Vector2f pos) {
        amount = am;
        type   = t;
        ID     = type+1;

        body.resize(4);
        body.setPrimitiveType(sf::Quads);

        body[0].position  = pos;
        body[1].position  = sf::Vector2f(pos.x+80, pos.y);
        body[2].position  = sf::Vector2f(pos.x+80, pos.y+80);
        body[3].position  = sf::Vector2f(pos.x   , pos.y+80);

        int tu = (type+32)%16;
        int tv = (type+32)/16;

        body[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);
    }

    Cash::~Cash() {}

    void Cash::draw(sf::RenderWindow& rw) {
        rw.draw(body, &resources.texture.items);
    }

    void Cash::update() {
        boundBox = sf::FloatRect(body[0].position.x, body[0].position.y, 16, 16);
    }

}
