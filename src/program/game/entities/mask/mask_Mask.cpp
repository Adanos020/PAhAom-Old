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

        body_.resize(4);
        body_.setPrimitiveType(sf::Quads);

        rr::setPosition(body_, sf::Vector2f(0, 0));
        setSize(body_, sf::Vector2f(80, 80));
        setColor(body_, sf::Color::Black);
    }

    void Mask::see(bool seen) {
        if (seen) {
            setColor(body_, sf::Color::Transparent);
            discovered_ = true;
        }
        else {
            if (discovered_)
                setColor(body_, sf::Color(0, 0, 0, 160));
            else
                setColor(body_, sf::Color::Black);
        }
        seen_ = seen;
    }

    void Mask::setFadeOut(sf::Color shades[]) {
        /*if (  (  shades[0] == sf::Color::Transparent
              && shades[1] == sf::Color(0, 0, 0, 160)
              && shades[2] == sf::Color::Transparent
              && shades[3] == sf::Color(0, 0, 0, 160)
               )
           || (  shades[0] == sf::Color(0, 0, 0, 160)
              && shades[1] == sf::Color::Black
              && shades[2] == sf::Color(0, 0, 0, 160)
              && shades[3] == sf::Color::Black
               )
           || (  shades[0] == sf::Color::Transparent
              && shades[1] == sf::Color::Black
              && shades[2] == sf::Color::Transparent
              && shades[3] == sf::Color::Black
               )
            )
        {
            sf::Color temp = shades[0];

            shades[0] = shades[1];
            shades[1] = shades[2];
            shades[2] = shades[3];
            shades[3] = temp;
        }*/
        setGradient(body_, shades);
    }

    void Mask::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

}
