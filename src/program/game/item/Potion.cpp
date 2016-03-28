/**
 * @file src/program/game/item/Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "item.h"

namespace rr {

    Potion::Potion(double id, std::string itemName, short icon, int am, short val, sf::Vector2f pos) {
        name = itemName;
        amount = am;
        bonus = val;
        disposable = true;

        skin.loadFromFile("data/graphics/items.png");

        body.setPrimitiveType(sf::Quads);
        body.resize(4);

        int tu = icon%(280/14);
        int tv = icon/(280/14);

        body[0].position = pos;
        body[1].position = sf::Vector2f(pos.x+70, pos.y);
        body[2].position = sf::Vector2f(pos.x+70, pos.y+70);
        body[3].position = sf::Vector2f(pos.x, pos.y+70);

        body[0].texCoords = sf::Vector2f(tu*14, tv*14);
        body[1].texCoords = sf::Vector2f((tu+1)*14, tv*14);
        body[2].texCoords = sf::Vector2f((tu+1)*14, (tv+1)*14);
        body[3].texCoords = sf::Vector2f(tu*14, (tv+1)*14);
    }

    Potion::~Potion() {}

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(body, &skin);
    }

    void Potion::editAmount(int am) {
        amount = am;
    }

    void Potion::update() {
        boundBox = body.getBounds();
    }

}
