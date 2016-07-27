/**
 * @file src/program/game/entity/Shadow.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Shadow.hpp"

#include "../../funcs/files.hpp"

namespace rr {

    Shadow::Shadow() :
      Entity     (                  ),
      position_  (sf::Vector2i(0, 0)),
      seen_      (false             ),
      discovered_(false             ),
      flipped_   (false             ) {

        initialize();
    }

    Shadow::Shadow(Shadow const& shadow) :
      Entity     (                  ),
      body_      (shadow.body_      ),
      position_  (shadow.position_  ),
      seen_      (shadow.seen_      ),
      discovered_(shadow.discovered_),
      flipped_   (shadow.flipped_   ) {}

    void Shadow::initialize() {
        body_.resize(4);
        body_.setPrimitiveType(sf::Quads);

        rr::setPosition(body_, sf::Vector2f(0, 0));
        setSize        (body_, sf::Vector2f(80, 80));
        setColor       (body_, sf::Color::Black);
    }

    void Shadow::see(bool seen) {
        if (  seen
            ) discovered_ = true;
        seen_ = seen;
    }

    void Shadow::setFadeOut(sf::Color shades[]) {
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

                if     (!flipped_ && (shades[0] == sf::Color::Black || shades[0] == sf::Color(0, 0, 0, 200))
                                  && (shades[2] == sf::Color::Black || shades[2] == sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = true;
                }
                else if (flipped_ && (shades[1] == sf::Color::Black || shades[1] == sf::Color(0, 0, 0, 200))
                                  && (shades[3] == sf::Color::Black || shades[3] == sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = false;
                }
                else if (flipped_ && (shades[0] != sf::Color::Black && shades[0] != sf::Color(0, 0, 0, 200))
                                  && (shades[2] != sf::Color::Black && shades[2] != sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = false;
                }

#else

                if     (!flipped_ && (shades[1] == sf::Color::Black || shades[1] == sf::Color(0, 0, 0, 200))
                                  && (shades[3] == sf::Color::Black || shades[3] == sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = true;
                }
                else if (flipped_ && (shades[0] == sf::Color::Black || shades[0] == sf::Color(0, 0, 0, 200))
                                  && (shades[2] == sf::Color::Black || shades[2] == sf::Color(0, 0, 0, 200))) {
                    flipVertically(body_);
                    flipped_ = false;
                }
                else if (flipped_ && (shades[1] != sf::Color::Black && shades[1] != sf::Color(0, 0, 0, 200))
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

    void Shadow::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

    std::ifstream& Shadow::operator<<(std::ifstream& file) {
        try {
            readFile <bool> (file, discovered_);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        initialize();

        return file;
    }

    std::ofstream& Shadow::operator>>(std::ofstream& file) {
        file << discovered_;

        return file;
    }

}
