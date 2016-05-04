/**
 * @file src/program/game/entities/door/door_Door.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "../../../program.hpp"

#include <iostream>

extern rr::Resources resources;

namespace rr {

    Door::Door(bool lock) {
        _locked     = lock;
        _open       = false;
        _withoutWindow = rand()%2;

        _body.setTexture(resources.texture.objects);
        _body.setScale(sf::Vector2f(5, 5));
        _body.setTextureRect(sf::IntRect(sf::Vector2i(rand()%5*16*(_withoutWindow+1), 0), sf::Vector2i(16, 16)));
    }

    Door::~Door() {}

    void Door::setOpen(bool b) {
        _open = b;
        if (_open)
            _body.setTextureRect(sf::IntRect(sf::Vector2i(_body.getTextureRect().left%80, 16),
                                             sf::Vector2i(16, 16)));
        else
            _body.setTextureRect(sf::IntRect(sf::Vector2i(_body.getTextureRect().left%80+80*_withoutWindow, 0),
                                             sf::Vector2i(16, 16)));
    }

    void Door::draw(sf::RenderWindow& rw) {
        rw.draw(_body);
    }

}
