/**
 * @file src/program/game/shadowmap/ShadowMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../funcs/files.hpp"
#include "../../Resources.hpp"

#include "ShadowMap.hpp"

namespace rr {

    ShadowMap::ShadowMap(sf::Vector2i size) :
      size_(size)
    {
        shadows_.create(3*size_.x, 3*size_.y, sf::Color::Black);

        for (int i=0; i<size.x*size.y; ++i) {
            discovered_[i] = false;
        }
    }

    void ShadowMap::fillCell(int x, int y, sf::Color c) {
        x *= 3; // setting the pixel coordinates to
        y *= 3; // the top-left edge of the cell

        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                shadows_.setPixel(x+i, y+j, c);
            }
        }
    }

    void ShadowMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::Texture stt;
        stt.loadFromImage(shadows_);
        stt.setSmooth(true);
        
        sf::Sprite sts(stt);
        sts.setScale(80.f/3.f, 80.f/3.f);

        target.draw(sts, states);
    }

    void ShadowMap::setLit(int x, int y) {
        discovered_[x + y*size_.x] = true;

        int tx = 3*x + 1, ty = 3*y + 1;

        shadows_.setPixel(tx, ty, sf::Color::Transparent);

        if (x < size_.x) {
            if (y > 0) {
                if (shadows_.getPixel(tx+3, ty-3) == sf::Color::Transparent) {  // TOP RIGHT
                    shadows_.setPixel(tx+1, ty-1,    sf::Color::Transparent);
                    shadows_.setPixel(tx+2, ty-2,    sf::Color::Transparent);
                }
            }

            if (y < size_.y) {
                if (shadows_.getPixel(tx+3, ty+3) == sf::Color::Transparent) {  // BOTTOM RIGHT
                    shadows_.setPixel(tx+1, ty+1,    sf::Color::Transparent);
                    shadows_.setPixel(tx+2, ty+2,    sf::Color::Transparent);
                }
            }

            if (shadows_.getPixel(tx+3, ty) == sf::Color::Transparent) {        // RIGHT
                shadows_.setPixel(tx+1, ty,    sf::Color::Transparent);
                shadows_.setPixel(tx+2, ty,    sf::Color::Transparent);
            }
        }

        if (x > 0) {
            if (y > 0) {
                if (shadows_.getPixel(tx-3, ty-3) == sf::Color::Transparent) {  // TOP LEFT
                    shadows_.setPixel(tx-1, ty-1,    sf::Color::Transparent);
                    shadows_.setPixel(tx-2, ty-2,    sf::Color::Transparent);
                }
            }

            if (y < size_.y) {
                if (shadows_.getPixel(tx-3, ty+3) == sf::Color::Transparent) {  // BOTTOM LEFT
                    shadows_.setPixel(tx-1, ty+1,    sf::Color::Transparent);
                    shadows_.setPixel(tx-2, ty+2,    sf::Color::Transparent);
                }
            }

            if (shadows_.getPixel(tx-3, ty) == sf::Color::Transparent) {        // LEFT
                shadows_.setPixel(tx-1, ty,    sf::Color::Transparent);
                shadows_.setPixel(tx-2, ty,    sf::Color::Transparent);
            }
        }

        if (y > 0) {
            if (shadows_.getPixel(tx  , ty-3) == sf::Color::Transparent) {      // TOP
                shadows_.setPixel(tx  , ty-1,    sf::Color::Transparent);
                shadows_.setPixel(tx  , ty-2,    sf::Color::Transparent);
            }
        }

        if (y < size_.y) {
            if (shadows_.getPixel(tx  , ty+3) == sf::Color::Transparent) {      // BOTTOM
                shadows_.setPixel(tx  , ty+1,    sf::Color::Transparent);
                shadows_.setPixel(tx  , ty+2,    sf::Color::Transparent);
            }
        }

// CORRECTING THE FINAL SHAPE OF THE SHADOWS

        if (  shadows_.getPixel(tx-1,  ty ) == sf::Color::Transparent           // IF LEFT
           && shadows_.getPixel( tx , ty-1) == sf::Color::Transparent           // AND TOP ARE TRANSPARENT
            ) shadows_.setPixel(tx-1, ty-1,    sf::Color::Transparent);         // THEN SET TOP LEFT TO TRANSPARENT

        if (  shadows_.getPixel(tx-1,  ty ) == sf::Color::Transparent           // IF LEFT
           && shadows_.getPixel( tx , ty+1) == sf::Color::Transparent           // AND BOTTOM ARE TRANSPARENT
            ) shadows_.setPixel(tx-1, ty+1,    sf::Color::Transparent);         // THEN SET BOTTOM LEFT TO TRANSPARENT

        if (  shadows_.getPixel(tx+1,  ty ) == sf::Color::Transparent           // IF RIGHT
           && shadows_.getPixel( tx , ty-1) == sf::Color::Transparent           // AND TOP ARE TRANSPARENT
            ) shadows_.setPixel(tx+1, ty-1,    sf::Color::Transparent);         // THEN SET TOP RIGHT TO TRANSPARENT

        if (  shadows_.getPixel(tx+1,  ty ) == sf::Color::Transparent           // IF RIGHT
           && shadows_.getPixel( tx , ty+1) == sf::Color::Transparent           // AND BOTTOM ARE TRANSPARENT
            ) shadows_.setPixel(tx+1, ty+1,    sf::Color::Transparent);         // THEN SET BOTTOM RIGHT TO TRANSPARENT

        if (  shadows_.getPixel(tx-1, ty-1) == sf::Color::Transparent           // IF TOP LEFT
           && shadows_.getPixel(tx-1, ty+1) == sf::Color::Transparent           // AND BOTTOM LEFT ARE TRANSPARENT
            ) shadows_.setPixel(tx-1,  ty ,    sf::Color::Transparent);         // THEN SET LEFT TO TRANSPARENT

        if (  shadows_.getPixel(tx-1, ty-1) == sf::Color::Transparent           // IF TOP LEFT
           && shadows_.getPixel(tx+1, ty-1) == sf::Color::Transparent           // AND TOP RIGHT ARE TRANSPARENT
            ) shadows_.setPixel( tx , ty-1,    sf::Color::Transparent);         // THEN SET TOP TO TRANSPARENT

        if (  shadows_.getPixel(tx+1, ty+1) == sf::Color::Transparent           // IF BOTTOM RIGHT
           && shadows_.getPixel(tx+1, ty-1) == sf::Color::Transparent           // AND TOP RIGHT ARE TRANSPARENT
            ) shadows_.setPixel(tx+1,  ty ,    sf::Color::Transparent);         // THEN SET RIGHT TO TRANSPARENT

        if (  shadows_.getPixel(tx+1, ty+1) == sf::Color::Transparent           // IF BOTTOM RIGHT
           && shadows_.getPixel(tx-1, ty+1) == sf::Color::Transparent           // AND BOTTOM LEFT ARE TRANSPARENT
            ) shadows_.setPixel( tx , ty+1,    sf::Color::Transparent);         // THEN SET BOTTOM TO TRANSPARENT
    }

    void ShadowMap::darken() {
        shadows_.create(3*size_.x, 3*size_.y, sf::Color::Black);
        for (int x=0; x<size_.x; ++x) {
            for (int y=0; y<size_.y; ++y) {
                if (  discovered_[x + y*size_.x]
                    ) fillCell(x, y, sf::Color(0, 0, 0, 200));
            }
        }
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
