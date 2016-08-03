/**
 * @file src/program/game/shadowmap/ShadowMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../funcs/files.hpp"

#include "ShadowMap.hpp"

namespace rr {

    ShadowMap::ShadowMap(sf::Vector2i size) :
      size_(size)
    {
        shadows_.setPrimitiveType(sf::Quads);
        shadows_.resize(size.x*size.y*4);
        
        for (int x=0; x<size.x; ++x) {
            for (int y=0; y<size.y; ++y) {
                int index = (x + y*size.x)*4;
                
                shadows_[index + 0].position = sf::Vector2f(  x * 80,   y * 80);
                shadows_[index + 1].position = sf::Vector2f((x+1)*80,   y * 80);
                shadows_[index + 2].position = sf::Vector2f((x+1)*80, (y+1)*80);
                shadows_[index + 3].position = sf::Vector2f(  x * 80, (y+1)*80);
            }
        }

        for (int i=0; i<size.x*size.y; ++i) {
            discovered_[i] = false;
            flipped_   [i] = false;
        }
    }

    void ShadowMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shadows_, states);
    }

    void ShadowMap::setLit(sf::Vector2i pos) {
        int index = (pos.x + size_.x*pos.y)*4;
                                                                /////////
        shadows_[index + 0].color = sf::Color::Transparent;     // --- //
        shadows_[index + 1].color = sf::Color::Transparent;     // -O- //
        shadows_[index + 2].color = sf::Color::Transparent;     // --- //
        shadows_[index + 3].color = sf::Color::Transparent;     /////////
#if 0
        if (pos.x > 0 && pos.x < size_.x && pos.y > 0 && pos.y < size_.y) {
            index = ((pos.x-1) + (pos.y-1)*size_.x)*4;          /////////
            shadows_[index + 2].color = sf::Color::Transparent; // O-- //
                                                                // --- //
                                                                // --- //
                                                                /////////
            
            index = (pos.x + (pos.y-1)*size_.x)*4;              /////////
            shadows_[index + 2].color = sf::Color::Transparent; // -O- //
            shadows_[index + 3].color = sf::Color::Transparent; // --- //
                                                                // --- //
                                                                /////////

            index = ((pos.x+1) + (pos.y-1)*size_.x)*4;          /////////
            shadows_[index + 3].color = sf::Color::Transparent; // --O //
                                                                // --- //
                                                                // --- //
                                                                /////////

            index = ((pos.x+1) + pos.y*size_.x)*4;              /////////
            shadows_[index + 0].color = sf::Color::Transparent; // --- //
            shadows_[index + 3].color = sf::Color::Transparent; // --O //
                                                                // --- //
                                                                /////////

            index = ((pos.x+1) + (pos.y+1)*size_.x)*4;          /////////
            shadows_[index + 0].color = sf::Color::Transparent; // --- //
                                                                // --- //
                                                                // --O //
                                                                /////////

            index = (pos.x + (pos.y+1)*size_.x)*4;              /////////
            shadows_[index + 0].color = sf::Color::Transparent; // --- //
            shadows_[index + 1].color = sf::Color::Transparent; // --- //
                                                                // -O- //
                                                                /////////

            index = ((pos.x-1) + (pos.y+1)*size_.x)*4;          /////////
            shadows_[index + 1].color = sf::Color::Transparent; // --- //
                                                                // --- //
                                                                // O-- //
                                                                /////////

            index = ((pos.x-1) + pos.y*size_.x)*4;              /////////
            shadows_[index + 1].color = sf::Color::Transparent; // --- //
            shadows_[index + 2].color = sf::Color::Transparent; // O-- //
                                                                // --- //
                                                                /////////
        }
#endif
        index = pos.x + size_.x*pos.y;
        discovered_[index] = true;
    }

    void ShadowMap::darken() {
        int index = 0;
        for (int x=0; x<size_.x; ++x) {
            for (int y=0; y<size_.y; ++y) {
                index = (x + y*size_.x)*4;
                if (discovered_[index/4]) {                             
                    shadows_[index + 0].color = sf::Color(0, 0, 0, 200);
                    shadows_[index + 1].color = sf::Color(0, 0, 0, 200);
                    shadows_[index + 2].color = sf::Color(0, 0, 0, 200);
                    shadows_[index + 3].color = sf::Color(0, 0, 0, 200);
                }
                else {
                    shadows_[index + 0].color = sf::Color::Black;
                    shadows_[index + 1].color = sf::Color::Black;
                    shadows_[index + 2].color = sf::Color::Black;
                    shadows_[index + 3].color = sf::Color::Black;
                }
            }
        }
#if 0
        for (int x=0; x<size_.x; ++x) {
            for (int y=0; y<size_.y; ++y) {
                index = (x + y*size_.x)*4;
                if (discovered_[index/4]) {                              /////////
                    shadows_[index + 0].color = sf::Color(0, 0, 0, 200); // --- //
                    shadows_[index + 1].color = sf::Color(0, 0, 0, 200); // -O- //
                    shadows_[index + 2].color = sf::Color(0, 0, 0, 200); // --- //
                    shadows_[index + 3].color = sf::Color(0, 0, 0, 200); /////////

                        if (.x > 0 && .x < size_.x && .y > 0 && .y < size_.y) {
                            index = ((x-1) + (y-1)*size_.x)*4;                   /////////
                            shadows_[index + 2].color = sf::Color(0, 0, 0, 200); // O-- //
                                                                                 // --- //
                                                                                 // --- //
                                                                                 /////////
                            
                            index = (x + (y-1)*size_.x)*4;                       /////////
                            shadows_[index + 2].color = sf::Color(0, 0, 0, 200); // -O- //
                            shadows_[index + 3].color = sf::Color(0, 0, 0, 200); // --- //
                                                                                 // --- //
                                                                                 /////////
    
                            index = ((x+1) + (y-1)*size_.x)*4;                   /////////
                            shadows_[index + 3].color = sf::Color(0, 0, 0, 200); // --O //
                                                                                 // --- //
                                                                                 // --- //
                                                                                 /////////
    
                            index = ((x+1) + y*size_.x)*4;                       /////////
                            shadows_[index + 0].color = sf::Color(0, 0, 0, 200); // --- //
                            shadows_[index + 3].color = sf::Color(0, 0, 0, 200); // --O //
                                                                                 // --- //
                                                                                 /////////
    
                            index = ((x+1) + (y+1)*size_.x)*4;                   /////////
                            shadows_[index + 0].color = sf::Color(0, 0, 0, 200); // --- //
                                                                                 // --- //
                                                                                 // --O //
                                                                                 /////////
    
                            index = (x + (y+1)*size_.x)*4;                       /////////
                            shadows_[index + 0].color = sf::Color(0, 0, 0, 200); // --- //
                            shadows_[index + 1].color = sf::Color(0, 0, 0, 200); // --- //
                                                                                 // -O- //
                                                                                 /////////
    
                            index = ((x-1) + (y+1)*size_.x)*4;                   /////////
                            shadows_[index + 1].color = sf::Color(0, 0, 0, 200); // --- //
                                                                                 // --- //
                                                                                 // O-- //
                                                                                 /////////
    
                            index = ((x-1) + y*size_.x)*4;                       /////////
                            shadows_[index + 1].color = sf::Color(0, 0, 0, 200); // --- //
                            shadows_[index + 2].color = sf::Color(0, 0, 0, 200); // O-- //
                                                                                 // --- //
                                                                                 /////////
                    }
                }
            }
        }
#endif
    }

    std::ifstream& ShadowMap::operator<<(std::ifstream& file) {
        try {
            for (int x=0; x<size_.x; ++x) {
                for (int y=0; y<size_.y; ++y) {
                    readFile <bool> (file, discovered_[x + y*size_.x]);
                }
            }
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        return file;
    }

    std::ofstream& ShadowMap::operator>>(std::ofstream& file) {
        for (int x=0; x<size_.x; ++x) {
            for (int y=0; y<size_.y; ++y) {
                file << discovered_[x + y*size_.x] << ' ';
            }
            file << '\n';
        }

        return file;
    }

}

/*
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
*/
