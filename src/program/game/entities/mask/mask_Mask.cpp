/**
 * @file src/program/game/entities/mask/mask_Mask.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "mask.hpp"

namespace rr {

    Mask::Mask()
        : Entity     (),
          position_  (sf::Vector2i(0, 0)),
          seen_      (false),
          discovered_(false) {

        body_.setPosition(sf::Vector2f(0, 0));
        body_.setSize(sf::Vector2f(80, 80));
        body_.setFillColor(sf::Color::Black);
    }

    void Mask::see(bool seen) {
        if (seen) {
            body_.setFillColor(sf::Color::Transparent);
            discovered_ = true;
        }
        else {
            if (discovered_)
                body_.setFillColor(sf::Color(0, 0, 0, 128));
            else
                body_.setFillColor(sf::Color::Black);
        }
        seen_ = seen;
    }

    void Mask::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

}
