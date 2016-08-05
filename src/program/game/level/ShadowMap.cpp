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
        shadowTexture_.create(3*size_.x, 3*size_.y);
        shadowTexture_.setSmooth(true);

        for (int i=0; i<size.x*size.y; ++i) {
            discovered_[i] = false;
        }
    }

    void ShadowMap::setColor(int x, int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) {
        shadows_[4*(x + y*size_.x) + 0] = r;
        shadows_[4*(x + y*size_.x) + 1] = g;
        shadows_[4*(x + y*size_.x) + 2] = b;
        shadows_[4*(x + y*size_.x) + 3] = a;
    }

    sf::Color ShadowMap::getColor(int x, int y) const {
        sf::Color c;

        c.r = shadows_[4*(x + y*size_.x) + 0];
        c.g = shadows_[4*(x + y*size_.x) + 1];
        c.b = shadows_[4*(x + y*size_.x) + 2];
        c.a = shadows_[4*(x + y*size_.x) + 3];

        return c;
    }

    void ShadowMap::fillCell(int x, int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) {
        x *= 3; // setting the pixel coordinates to
        y *= 3; // the top-left edge of the cell

        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                setColor(x+i, y+j, r, g, b, a);
            }
        }
    }

    bool ShadowMap::isFilled(int x, int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) const {
        if (  x < 0 || x > size_.x-1
           || y < 0 || y > size_.y-1
            ) return false;

        int tx = 3*x, ty = 3*y;

        bool filled = true;

        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                if (getColor(tx+i, ty+j) != sf::Color(r, g, b, a)) {
                    filled = false;
                    break;
                } 
            }
        }

        return filled;
    }

    void ShadowMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        shadowTexture_.update(shadows_);

        sf::Sprite sts(shadowTexture_);
        sts.setScale(80.f/3.f, 80.f/3.f);

        target.draw(sts, states);
    }

    void ShadowMap::setLit(int x, int y) {
        discovered_[x + y*size_.x] = true;

        int tx = 3*x + 1, ty = 3*y + 1;

        setColor(tx, ty, 0, 0, 0, 0);

        if (x < size_.x-1) {
            if (y > 0) {
                if (getColor(tx+3, ty-3) == sf::Color::Transparent) {  // TOP RIGHT
                    setColor(tx+1, ty-1, 0, 0, 0, 0);
                    setColor(tx+1,  ty , 0, 0, 0, 0);
                    setColor( tx , ty-1, 0, 0, 0, 0);

                    setColor(tx+2, ty-2, 0, 0, 0, 0);
                }
            }

            if (y < size_.y-1) {
                if (getColor(tx+3, ty+3) == sf::Color::Transparent) {  // BOTTOM RIGHT
                    setColor(tx+1, ty+1, 0, 0, 0, 0);
                    setColor(tx+1,  ty , 0, 0, 0, 0);
                    setColor( tx , ty+1, 0, 0, 0, 0);

                    setColor(tx+2, ty+2, 0, 0, 0, 0);
                }
            }

            if (getColor(tx+3, ty) == sf::Color::Transparent) {        // RIGHT
                setColor(tx+1, ty, 0, 0, 0, 0);
                setColor(tx+2, ty, 0, 0, 0, 0);
            }
        }

        if (x > 0) {
            if (y > 0) {
                if (getColor(tx-3, ty-3) == sf::Color::Transparent) {  // TOP LEFT
                    setColor(tx-1, ty-1, 0, 0, 0, 0);
                    setColor(tx-1,  ty , 0, 0, 0, 0);
                    setColor( tx , ty-1, 0, 0, 0, 0);

                    setColor(tx-2, ty-2, 0, 0, 0, 0);
                }
            }

            if (y < size_.y-1) {
                if (getColor(tx-3, ty+3) == sf::Color::Transparent) {  // BOTTOM LEFT
                    setColor(tx-1, ty+1, 0, 0, 0, 0);
                    setColor(tx-1,  ty , 0, 0, 0, 0);
                    setColor( tx , ty+1, 0, 0, 0, 0);

                    setColor(tx-2, ty+2, 0, 0, 0, 0);
                }
            }

            if (getColor(tx-3, ty) == sf::Color::Transparent) {        // LEFT
                setColor(tx-1, ty, 0, 0, 0, 0);
                setColor(tx-2, ty, 0, 0, 0, 0);
            }
        }

        if (y > 0) {
            if (getColor(tx  , ty-3) == sf::Color::Transparent) {      // TOP
                setColor(tx  , ty-1, 0, 0, 0, 0);
                setColor(tx  , ty-2, 0, 0, 0, 0);
            }
        }

        if (y < size_.y-1) {
            if (getColor(tx  , ty+3) == sf::Color::Transparent) {      // BOTTOM
                setColor(tx  , ty+1, 0, 0, 0, 0);
                setColor(tx  , ty+2, 0, 0, 0, 0);
            }
        }

// CORRECTING THE FINAL SHAPE OF THE SHADOWS
/*
        if (  isFilled(x, y, sf::Color::Transparent)
            ) return;

        if (  isFilled(x-1, y-1, sf::Color::Transparent)
           && isFilled( x , y-1, sf::Color::Transparent)
           && isFilled(x+1, y-1, sf::Color::Transparent)
           && isFilled(x+1,  y , sf::Color::Transparent)
           && isFilled(x+1, y+1, sf::Color::Transparent)
           && isFilled( x , y+1, sf::Color::Transparent)
           && isFilled(x-1, y+1, sf::Color::Transparent)
           && isFilled(x-1,  y , sf::Color::Transparent)
            ) return;
*/
        std::vector<char> neighbors;
        if (x > 0) {
            if (  y > 0
                ) neighbors.push_back(1);

            if (  y < size_.y-1
                ) neighbors.push_back(7);

            neighbors.push_back(8);
        }

        if (x < size_.x-1) {
            if (  y > 0
                ) neighbors.push_back(3);

            if (  y < size_.y-1
                ) neighbors.push_back(5);

            neighbors.push_back(4);
        }
        
        if (  y > 0
            ) neighbors.push_back(2);

        if (  y < size_.y-1
            ) neighbors.push_back(6);

        for (unsigned i=0; i<neighbors.size(); ++i) {
            switch (neighbors[i]) {    // here we switch between the central cell and the cells next to it
                case 0: tx = 3*( x ) + 1; ty = 3*( y ) + 1; break;              // CENTER
                case 1: tx = 3*(x-1) + 1; ty = 3*(y-1) + 1; break;              // TOP LEFT
                case 2: tx = 3*( x ) + 1; ty = 3*(y-1) + 1; break;              // TOP
                case 3: tx = 3*(x+1) + 1; ty = 3*(y-1) + 1; break;              // TOP RIGHT
                case 4: tx = 3*(x+1) + 1; ty = 3*( y ) + 1; break;              // RIGHT
                case 5: tx = 3*(x+1) + 1; ty = 3*(y+1) + 1; break;              // BOTTOM RIGHT
                case 6: tx = 3*( x ) + 1; ty = 3*(y+1) + 1; break;              // BOTTOM
                case 7: tx = 3*(x-1) + 1; ty = 3*(y+1) + 1; break;              // BOTTOM LEFT
                case 8: tx = 3*(x-1) + 1; ty = 3*( y ) + 1; break;              // LEFT
            }

            if (  getColor(tx-1,  ty ) == sf::Color::Transparent       // IF LEFT
               && getColor( tx , ty-1) == sf::Color::Transparent       // AND TOP ARE TRANSPARENT
                ) setColor(tx-1, ty-1, 0, 0, 0, 0);                    // THEN SET TOP LEFT TO TRANSPARENT

            if (  getColor(tx-1,  ty ) == sf::Color::Transparent       // IF LEFT
               && getColor( tx , ty+1) == sf::Color::Transparent       // AND BOTTOM ARE TRANSPARENT
                ) setColor(tx-1, ty+1, 0, 0, 0, 0);                    // THEN SET BOTTOM LEFT TO TRANSPARENT

            if (  getColor(tx+1,  ty ) == sf::Color::Transparent       // IF RIGHT
               && getColor( tx , ty-1) == sf::Color::Transparent       // AND TOP ARE TRANSPARENT
                ) setColor(tx+1, ty-1, 0, 0, 0, 0);                    // THEN SET TOP RIGHT TO TRANSPARENT

            if (  getColor(tx+1,  ty ) == sf::Color::Transparent       // IF RIGHT
               && getColor( tx , ty+1) == sf::Color::Transparent       // AND BOTTOM ARE TRANSPARENT
                ) setColor(tx+1, ty+1, 0, 0, 0, 0);                    // THEN SET BOTTOM RIGHT TO TRANSPARENT

            if (  getColor(tx-1, ty-1) == sf::Color::Transparent       // IF TOP LEFT
               && getColor(tx-1, ty+1) == sf::Color::Transparent       // AND BOTTOM LEFT ARE TRANSPARENT
                ) setColor(tx-1,  ty , 0, 0, 0, 0);                    // THEN SET LEFT TO TRANSPARENT

            if (  getColor(tx-1, ty-1) == sf::Color::Transparent       // IF TOP LEFT
               && getColor(tx+1, ty-1) == sf::Color::Transparent       // AND TOP RIGHT ARE TRANSPARENT
                ) setColor( tx , ty-1, 0, 0, 0, 0);                    // THEN SET TOP TO TRANSPARENT

            if (  getColor(tx+1, ty+1) == sf::Color::Transparent       // IF BOTTOM RIGHT
               && getColor(tx+1, ty-1) == sf::Color::Transparent       // AND TOP RIGHT ARE TRANSPARENT
                ) setColor(tx+1,  ty , 0, 0, 0, 0);                    // THEN SET RIGHT TO TRANSPARENT

            if (  getColor(tx+1, ty+1) == sf::Color::Transparent       // IF BOTTOM RIGHT
               && getColor(tx-1, ty+1) == sf::Color::Transparent       // AND BOTTOM LEFT ARE TRANSPARENT
                ) setColor( tx , ty+1, 0, 0, 0, 0);                    // THEN SET BOTTOM TO TRANSPARENT
        }
    }

    void ShadowMap::darken() {
        for (int i=0; i<4*77*43; ++i) {
            shadows_[i] = ((i+1)%4 == 0 ? 255 : 0);
        }
        for (int x=0; x<size_.x; ++x) {
            for (int y=0; y<size_.y; ++y) {
                if (  discovered_[x + y*size_.x]
                    ) fillCell(x, y, 0, 0, 0, 200);
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
