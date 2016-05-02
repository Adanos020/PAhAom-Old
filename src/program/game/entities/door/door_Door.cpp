/**
 * @file src/program/game/entities/door/door_Door.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Door::Door(bool lock) {
        locked = lock;
        open   = false;

        body.setTexture(resources.texture.objects);
        body.setScale(sf::Vector2f(5, 5));
        body.setTextureRect(sf::IntRect(sf::Vector2i(rand()%10*16, 0), sf::Vector2i(16, 16)));
    }

    Door::~Door() {}

    void Door::setOpen(bool b) {
        open = b;
        if (open)
            body.setTextureRect(sf::IntRect(sf::Vector2i(body.getTextureRect().left,
                                                         body.getTextureRect().top+16), sf::Vector2i(16, 16)));
        else
            body.setTextureRect(sf::IntRect(sf::Vector2i(body.getTextureRect().left,
                                                         body.getTextureRect().top-16), sf::Vector2i(16, 16)));
    }

    void Door::draw(sf::RenderWindow& rw) {
        rw.draw(body);
    }

}
