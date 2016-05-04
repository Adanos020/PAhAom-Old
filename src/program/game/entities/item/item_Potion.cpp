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
        _name       = "";
        _amount     = am;
        _effect     = e;
        _size       = s;
        _disposable = true;
        _discovered = false;
        _ID         = 100 + _size*10 + _effect;

        int tu = (_size+1)%16;
        int tv = (_size+1)/16;

        _body.resize(8);
        _body.setPrimitiveType(sf::Quads);

     // setting the vertices of the flask
        _body[0].position = (sf::Vector2f)pos*80.f;
        _body[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        _body[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        _body[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        _body[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        _body[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        _body[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        _body[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);

     // setting the vertices of the liqu_ID
        _body[4].position  = _body[0].position;
        _body[5].position  = _body[1].position;
        _body[6].position  = _body[2].position;
        _body[7].position  = _body[3].position;

        _body[4].texCoords = _body[0].texCoords+sf::Vector2f(0, 16);
        _body[5].texCoords = _body[1].texCoords+sf::Vector2f(0, 16);
        _body[6].texCoords = _body[2].texCoords+sf::Vector2f(0, 16);
        _body[7].texCoords = _body[3].texCoords+sf::Vector2f(0, 16);

        _body[4].color     = potionColors[_effect];
        _body[5].color     = potionColors[_effect];
        _body[6].color     = potionColors[_effect];
        _body[7].color     = potionColors[_effect];
    }

    Potion::~Potion() {}

    void Potion::reveal() {
        _discovered = true;
    }

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(_body, &resources.texture.items);
    }

    void Potion::update() {}

    void Potion::setPosition(sf::Vector2i pos) {
        _body[0].position = (sf::Vector2f)pos*80.f;
        _body[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        _body[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        _body[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        _body[4].position = _body[0].position;
        _body[5].position = _body[1].position;
        _body[6].position = _body[2].position;
        _body[7].position = _body[3].position;
    }

}
