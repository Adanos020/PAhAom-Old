/**
 * @file src/program/game/item/item_Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "item_Potion.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;
extern sf::Color     potionColors[9];

namespace rr {

    Potion::Potion(Effect e, Size s, int am, sf::Vector2i pos) {
        name       = "";
        amount     = am;
        effect     = e;
        size       = s;
        disposable = true;
        discovered = false;
        ID         = 100 + size*10 + effect;

        int tu = (size+1)%16;
        int tv = (size+1)/16;

        body.resize(8);
        body.setPrimitiveType(sf::Quads);

     // setting the vertices of the flask
        body[0].position  = (sf::Vector2f)pos*80.f;
        body[1].position  = sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        body[2].position  = sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body[3].position  = sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);

     // setting the vertices of the liquid
        body[4].position  = body[0].position;
        body[5].position  = body[1].position;
        body[6].position  = body[2].position;
        body[7].position  = body[3].position;

        body[4].texCoords = body[0].texCoords+sf::Vector2f(0, 16);
        body[5].texCoords = body[1].texCoords+sf::Vector2f(0, 16);
        body[6].texCoords = body[2].texCoords+sf::Vector2f(0, 16);
        body[7].texCoords = body[3].texCoords+sf::Vector2f(0, 16);

        body[4].color     = potionColors[effect];
        body[5].color     = potionColors[effect];
        body[6].color     = potionColors[effect];
        body[7].color     = potionColors[effect];
    }

    Potion::~Potion() {}

    void Potion::reveal() {
        discovered = true;
    }

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(body, &resources.texture.items);
    }

    void Potion::update() {
        boundBox = sf::FloatRect(body[0].position.x, body[0].position.y, 16, 16);
    }

    void Potion::setPosition(sf::Vector2i pos) {
        body[0].position = (sf::Vector2f)pos*80.f;
        body[1].position = sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body[2].position = sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body[3].position = sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body[4].position = body[0].position;
        body[5].position = body[1].position;
        body[6].position = body[2].position;
        body[7].position = body[3].position;
    }

}
