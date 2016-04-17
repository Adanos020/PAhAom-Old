/**
 * @file src/program/game/item/item_Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "item_Potion.hpp"
#include "../../program.hpp"

#include <string>

extern rr::Resources resources;
extern sf::Color potionColors[9];

namespace rr {

    Potion::Potion(Effect e, Size s, int am, sf::Vector2f pos) {
        name       = "";
        amount     = am;
        effect     = e;
        size       = s;
        disposable = true;
        discovered = false;
        ID         = 383;

        int tu = (size+1)%20;
        int tv = (size+1)/20;

        body.resize(4);
        body.setPrimitiveType(sf::Quads);

        body[0].position = pos;
        body[1].position = sf::Vector2f(pos.x+70, pos.y);
        body[2].position = sf::Vector2f(pos.x+70, pos.y+70);
        body[3].position = sf::Vector2f(pos.x   , pos.y+70);

        body[0].texCoords = sf::Vector2f( tu*14   ,  tv*14);
        body[1].texCoords = sf::Vector2f((tu+1)*14,  tv*14);
        body[2].texCoords = sf::Vector2f((tu+1)*14, (tv+1)*14);
        body[3].texCoords = sf::Vector2f( tu*14   , (tv+1)*14);

        body[0].color = sf::Color::White;
        body[1].color = sf::Color::White;
        body[2].color = potionColors[effect];
        body[3].color = potionColors[effect];
    }

    Potion::~Potion() {}

    void Potion::reveal() {
        discovered = true;
    }

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(body, &resources.texture.items);
    }

    void Potion::update() {
        boundBox = sf::FloatRect(body[0].position.x, body[0].position.y, 14, 14);
    }

}
