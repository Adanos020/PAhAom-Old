/**
 * @file src/program/game/entity/Door.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../Resources.hpp"

#include "../../funcs/files.hpp"

#include "Door.hpp"

namespace rr {

    Door::Door(bool lock) :
      locked_        (lock    ),
      open_          (false   ),
      withoutWindow_ (rand()%2)
    {
        initialize();
    }

    Door::Door(Door const& copy) :
      body_         (copy.body_         ),
      locked_       (copy.locked_       ),
      open_         (copy.open_         ),
      withoutWindow_(copy.withoutWindow_) {}

    void Door::initialize() {
        body_.setTexture    (Resources::texture.objects);
        body_.setScale      (sf::Vector2f(5, 5));
        body_.setTextureRect(sf::IntRect(sf::Vector2i(rand()%5*16*(withoutWindow_+1), 0), sf::Vector2i(16, 16)));
    }

    void Door::setOpen(bool b) {
        open_ = b;
        if (  open_
            ) body_.setTextureRect(sf::IntRect(sf::Vector2i(body_.getTextureRect().left%80, 16)                 , sf::Vector2i(16, 16)));
        else  body_.setTextureRect(sf::IntRect(sf::Vector2i(body_.getTextureRect().left%80+80*withoutWindow_, 0), sf::Vector2i(16, 16)));
    }

    void Door::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &Resources::texture.objects;
        target.draw(body_, states);
    }

    std::ifstream& Door::operator<<(std::ifstream& file) {
        sf::Vector2u position;

        try {
            readFile <unsigned> (file, position.x);
            readFile <unsigned> (file, position.y);
            readFile <  bool  > (file, locked_);
            readFile <  bool  > (file, open_);
            readFile <  bool  > (file, withoutWindow_);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Door::operator>>(std::ofstream& file) {
        file << 1                                    << ' '
             << (unsigned) body_.getPosition().x/80u << ' '
             << (unsigned) body_.getPosition().y/80u << ' '
             << locked_                              << ' '
             << open_                                << ' '
             << withoutWindow_;

        return file;
    }
}
