/**
 * @file src/program/game/item/item_Coin.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "item_Coin.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Coin::Coin(Type t, Size s, int am, sf::Vector2i pos) {
        _amount = am;
        _type   = t;
        _size   = s;
        _ID     = 3*_size + _type + 1;

        _body.resize(4);
        _body.setPrimitiveType(sf::Quads);

        _body[0].position = (sf::Vector2f)pos*80.f;
        _body[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        _body[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        _body[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        int tu = (_type+(_size+2)*16)%16;
        int tv = (_type+(_size+2)*16)/16;

        _body[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        _body[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        _body[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        _body[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);
    }

    Coin::~Coin() {}

    void Coin::draw(sf::RenderWindow& rw) {
        rw.draw(_body, &resources.texture.items);
    }

    void Coin::update() {}

}
