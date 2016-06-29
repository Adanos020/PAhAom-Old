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
      discovered_(false),
      flipped_   (false) {

        body_.resize(4);
        body_.setPrimitiveType(sf::Quads);

        rr::setPosition(body_, sf::Vector2f(0, 0));
        setSize(body_, sf::Vector2f(80, 80));
        setColor(body_, sf::Color::Black);
    }

    Mask::Mask(Mask const& mask)
    : Entity     (),
      body_      (mask.body_),
      position_  (mask.position_),
      seen_      (mask.seen_),
      discovered_(mask.discovered_),
      flipped_   (mask.flipped_) {}

    void Mask::see(bool seen) {
        if (seen) {
            discovered_ = true;
        }
        seen_ = seen;
    }

    void Mask::setFadeOut(sf::Color shades[]) {
        if (discovered_) {
            bool lightFound = false;
            for (int i=0; i<4; i++) {
                if (shades[i] == sf::Color::Transparent) {
                    lightFound = true;
                    break;
                }
            }

            if (lightFound) {

#ifdef __gnu_linux__

                if (  !flipped_
                   && (shades[0] == sf::Color::Black || shades[0] == sf::Color(0, 0, 0, 200))
                   && (shades[2] == sf::Color::Black || shades[2] == sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = true;
                }
                else if (flipped_
                     && (shades[1] == sf::Color::Black || shades[1] == sf::Color(0, 0, 0, 200))
                     && (shades[3] == sf::Color::Black || shades[3] == sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = false;
                }
                else if (flipped_
                     && (shades[0] != sf::Color::Black && shades[0] != sf::Color(0, 0, 0, 200))
                     && (shades[2] != sf::Color::Black && shades[2] != sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = false;
                }

#else

                if (  !flipped_
                   && (shades[1] == sf::Color::Black || shades[1] == sf::Color(0, 0, 0, 200))
                   && (shades[3] == sf::Color::Black || shades[3] == sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = true;
                }
                else if (flipped_
                     && (shades[0] == sf::Color::Black || shades[0] == sf::Color(0, 0, 0, 200))
                     && (shades[2] == sf::Color::Black || shades[2] == sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = false;
                }
                else if (flipped_
                     && (shades[1] != sf::Color::Black && shades[1] != sf::Color(0, 0, 0, 200))
                     && (shades[3] != sf::Color::Black && shades[3] != sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = false;
                }

#endif

            }

            if (flipped_) {
                sf::Color color_0 = shades[3],
                          color_1 = shades[2],
                          color_2 = shades[1],
                          color_3 = shades[0];
                shades[0] = color_0;
                shades[1] = color_1;
                shades[2] = color_2;
                shades[3] = color_3;
            }

            setGradient(body_, shades);
        }
    }

    void Mask::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

}
