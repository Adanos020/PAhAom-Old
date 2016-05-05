/**
 * @file src/program/game/entities/door/door_Door.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Door::Door(bool lock) {
        locked_        = lock;
        open_          = false;
        withoutWindow_ = rand()%2;

        body_.setTexture(resources.texture.objects);
        body_.setScale(sf::Vector2f(5, 5));
        body_.setTextureRect(sf::IntRect(sf::Vector2i(rand()%5*16*(withoutWindow_+1), 0), sf::Vector2i(16, 16)));
    }

    Door::~Door() {}

    void Door::setOpen(bool b) {
        open_ = b;
        if (open_)
            body_.setTextureRect(sf::IntRect(sf::Vector2i(body_.getTextureRect().left%80, 16),
                                             sf::Vector2i(16, 16)));
        else
            body_.setTextureRect(sf::IntRect(sf::Vector2i(body_.getTextureRect().left%80+80*withoutWindow_, 0),
                                             sf::Vector2i(16, 16)));
    }

    void Door::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

}
