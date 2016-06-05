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

    void Mask::setFadeOut(bool light[], sf::Color shadow, sf::Color bright) {
        sf::Color shades[4];
        if (discovered_) {
            for (int i=0; i<4; i++) {
                shades[i] = light[i] ? bright : shadow;
            }
        }

        setGradient(body_, shades);
        /*if (  (!light[0] &&  light[1] && !light[2] &&  light[3])
           || ( light[0] && !light[1] && !light[2] && !light[3])
           || (!light[0] && !light[1] && !light[2] &&  light[3])
            ) {
            auto temp = body_[3];
            body_[3]  = body_[2];
            body_[2]  = body_[1];
            body_[1]  = body_[0];
            body_[0]  = temp    ;
        }*/
    }

    void Mask::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

}
