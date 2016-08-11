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
        shadowImage_.create(size_.x*3, size_.y*3, sf::Color::Black);

        shadowTexture_.loadFromImage(shadowImage_);
        shadowTexture_.setSmooth(true);

        shadowSprite_.resize(4);
        shadowSprite_.setPrimitiveType(sf::Quads);

        shadowSprite_[0].position  = sf::Vector2f(0        , 0        );
        shadowSprite_[1].position  = sf::Vector2f(80*size.x, 0        );
        shadowSprite_[2].position  = sf::Vector2f(80*size.x, 80*size.y);
        shadowSprite_[3].position  = sf::Vector2f(0        , 80*size.y);

        shadowSprite_[0].texCoords = sf::Vector2f(0       , 0       );
        shadowSprite_[1].texCoords = sf::Vector2f(3*size.x, 0       );
        shadowSprite_[2].texCoords = sf::Vector2f(3*size.x, 3*size.y);
        shadowSprite_[3].texCoords = sf::Vector2f(0       , 3*size.y);

        for (int i=0; i<size_.x*size_.y; ++i) {
            discovered_[i] = false;
        }

        for (int i=0; i<size_.x*size_.y*9; ++i) {
            cellIDs_[i] = 0;
        }
    }

    bool ShadowMap::isFilled(int x, int y, unsigned char id) const {
        if (  x < 0 || x > size_.x-1
           || y < 0 || y > size_.y-1
            ) return false;

        int tx = 3*x, ty = 3*y;

        bool filled = true;

        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                if (cellIDs_[tx+i + (ty+j)*size_.x*3] == id) {
                    filled = false;
                    break;
                } 
            }
            if ( !filled
                ) break;
        }
        return filled;
    }

    void ShadowMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &shadowTexture_;
        target.draw(shadowSprite_, states);
    }

    void ShadowMap::setLit(int x, int y) {
        discovered_[x + y*size_.x] = true;

        int tx = 3*x + 1, ty = 3*y + 1;

        cellIDs_[tx + ty*size_.x*3] = 2;
        lastlyLit_.push_back(sf::Vector2i(tx, ty));

        if (x < size_.x-1) {
            if (y > 0) {
                if (cellIDs_[tx+3 + (ty-3)*size_.x*3] == 2) {  // TOP RIGHT
                    cellIDs_[tx+1 + (ty-1)*size_.x*3] =  2;
                    cellIDs_[tx+1 + ( ty )*size_.x*3] =  2;
                    cellIDs_[ tx  + (ty-1)*size_.x*3] =  2;

                    cellIDs_[tx+2 + (ty-2)*size_.x*3] =  2;

                    lastlyLit_.push_back(sf::Vector2i(tx+1, ty-1));
                    lastlyLit_.push_back(sf::Vector2i(tx+1,  ty ));
                    lastlyLit_.push_back(sf::Vector2i( tx , ty-1));
                    lastlyLit_.push_back(sf::Vector2i(tx+2, ty-2));
                }
            }

            if (y < size_.y-1) {
                if (cellIDs_[tx+3 + (ty+3)*size_.x*3] == 2) {  // BOTTOM RIGHT
                    cellIDs_[tx+1 + (ty+1)*size_.x*3] =  2;
                    cellIDs_[tx+1 + ( ty )*size_.x*3] =  2;
                    cellIDs_[ tx  + (ty+1)*size_.x*3] =  2;

                    cellIDs_[tx+2 + (ty+2)*size_.x*3] =  2;

                    lastlyLit_.push_back(sf::Vector2i(tx+1, ty+1));
                    lastlyLit_.push_back(sf::Vector2i(tx+1,  ty ));
                    lastlyLit_.push_back(sf::Vector2i( tx , ty+1));
                    lastlyLit_.push_back(sf::Vector2i(tx+2, ty+2));
                }
            }

            if (cellIDs_[tx+3 + ty*size_.x*3] == 2) {        // RIGHT
                cellIDs_[tx+1 + ty*size_.x*3] =  2;
                cellIDs_[tx+2 + ty*size_.x*3] =  2;

                lastlyLit_.push_back(sf::Vector2i(tx+1, ty));
                lastlyLit_.push_back(sf::Vector2i(tx+2, ty));
            }
        }

        if (x > 0) {
            if (y > 0) {
                if (cellIDs_[tx-3 + (ty-3)*size_.x*3] == 2) {  // TOP LEFT
                    cellIDs_[tx-1 + (ty-1)*size_.x*3] =  2;
                    cellIDs_[tx-1 + ( ty )*size_.x*3] =  2;
                    cellIDs_[ tx  + (ty-1)*size_.x*3] =  2;

                    cellIDs_[tx-2 + (ty-2)*size_.x*3] =  2;

                    lastlyLit_.push_back(sf::Vector2i(tx-1, ty-1));
                    lastlyLit_.push_back(sf::Vector2i(tx-1,  ty ));
                    lastlyLit_.push_back(sf::Vector2i( tx , ty-1));
                    lastlyLit_.push_back(sf::Vector2i(tx-2, ty-2));
                }
            }

            if (y < size_.y-1) {
                if (cellIDs_[tx-3 + (ty+3)*size_.x*3] == 2) {  // BOTTOM LEFT
                    cellIDs_[tx-1 + (ty+1)*size_.x*3] =  2;
                    cellIDs_[tx-1 + ( ty )*size_.x*3] =  2;
                    cellIDs_[ tx  + (ty+1)*size_.x*3] =  2;

                    cellIDs_[tx-2 + (ty+2)*size_.x*3] =  2;

                    lastlyLit_.push_back(sf::Vector2i(tx-1, ty+1));
                    lastlyLit_.push_back(sf::Vector2i(tx-1,  ty ));
                    lastlyLit_.push_back(sf::Vector2i( tx , ty+1));
                    lastlyLit_.push_back(sf::Vector2i(tx-2, ty+2));
                }
            }

            if (cellIDs_[tx-3 + ty*size_.x*3] == 2) {        // LEFT
                cellIDs_[tx-1 + ty*size_.x*3] =  2;
                cellIDs_[tx-2 + ty*size_.x*3] =  2;

                lastlyLit_.push_back(sf::Vector2i(tx-1, ty));
                lastlyLit_.push_back(sf::Vector2i(tx-2, ty));
            }
        }

        if (y > 0) {
            if (cellIDs_[tx + (ty-3)*size_.x*3] == 2) {      // TOP
                cellIDs_[tx + (ty-1)*size_.x*3] =  2;
                cellIDs_[tx + (ty-2)*size_.x*3] =  2;

                lastlyLit_.push_back(sf::Vector2i(tx, ty-1));
                lastlyLit_.push_back(sf::Vector2i(tx, ty-2));
            }
        }

        if (y < size_.y-1) {
            if (cellIDs_[tx + (ty+3)*size_.x*3] == 2) {      // BOTTOM
                cellIDs_[tx + (ty+1)*size_.x*3] =  2;
                cellIDs_[tx + (ty+2)*size_.x*3] =  2;

                lastlyLit_.push_back(sf::Vector2i(tx, ty+1));
                lastlyLit_.push_back(sf::Vector2i(tx, ty+2));
            }
        }

// CORRECTING THE FINAL SHAPE OF THE SHADOWS

        if (  isFilled(x, y, 2)
            ) return;

        if (  isFilled(x-1, y-1, 2)
           && isFilled( x , y-1, 2)
           && isFilled(x+1, y-1, 2)
           && isFilled(x+1,  y , 2)
           && isFilled(x+1, y+1, 2)
           && isFilled( x , y+1, 2)
           && isFilled(x-1, y+1, 2)
           && isFilled(x-1,  y , 2)
            ) return;

        std::vector<unsigned char> neighbors;
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
                case 0: tx = 3*( x ) + 1; ty = 3*( y ) + 1; break;  // CENTER
                case 1: tx = 3*(x-1) + 1; ty = 3*(y-1) + 1; break;  // TOP LEFT
                case 2: tx = 3*( x ) + 1; ty = 3*(y-1) + 1; break;  // TOP
                case 3: tx = 3*(x+1) + 1; ty = 3*(y-1) + 1; break;  // TOP RIGHT
                case 4: tx = 3*(x+1) + 1; ty = 3*( y ) + 1; break;  // RIGHT
                case 5: tx = 3*(x+1) + 1; ty = 3*(y+1) + 1; break;  // BOTTOM RIGHT
                case 6: tx = 3*( x ) + 1; ty = 3*(y+1) + 1; break;  // BOTTOM
                case 7: tx = 3*(x-1) + 1; ty = 3*(y+1) + 1; break;  // BOTTOM LEFT
                case 8: tx = 3*(x-1) + 1; ty = 3*( y ) + 1; break;  // LEFT
            }

            if (  cellIDs_[tx-1 + ( ty )*size_.x*3] == 2            // IF LEFT
               && cellIDs_[ tx  + (ty-1)*size_.x*3] == 2) {         // AND TOP ARE TRANSPARENT
                  cellIDs_[tx-1 + (ty-1)*size_.x*3] =  2;           // THEN SET TOP LEFT TO TRANSPARENT
                  lastlyLit_.push_back(sf::Vector2i(tx-1, ty-1));
            }

            if (  cellIDs_[tx-1 + ( ty )*size_.x*3] == 2            // IF LEFT
               && cellIDs_[ tx  + (ty+1)*size_.x*3] == 2) {         // AND BOTTOM ARE TRANSPARENT
                  cellIDs_[tx-1 + (ty+1)*size_.x*3] =  2;           // THEN SET BOTTOM LEFT TO TRANSPARENT
                  lastlyLit_.push_back(sf::Vector2i(tx-1, ty+1));
            }

            if (  cellIDs_[tx+1 + ( ty )*size_.x*3] == 2            // IF RIGHT
               && cellIDs_[ tx  + (ty-1)*size_.x*3] == 2) {         // AND TOP ARE TRANSPARENT
                  cellIDs_[tx+1 + (ty-1)*size_.x*3] =  2;           // THEN SET TOP RIGHT TO TRANSPARENT
                  lastlyLit_.push_back(sf::Vector2i(tx+1, ty-1));
            }

            if (  cellIDs_[tx+1 + ( ty )*size_.x*3] == 2            // IF RIGHT
               && cellIDs_[ tx  + (ty+1)*size_.x*3] == 2) {         // AND BOTTOM ARE TRANSPARENT
                  cellIDs_[tx+1 + (ty+1)*size_.x*3] =  2;           // THEN SET BOTTOM RIGHT TO TRANSPARENT
                  lastlyLit_.push_back(sf::Vector2i(tx+1, ty+1));
            }

            if (  cellIDs_[tx-1 + (ty-1)*size_.x*3] == 2            // IF TOP LEFT
               && cellIDs_[tx-1 + (ty+1)*size_.x*3] == 2) {         // AND BOTTOM LEFT ARE TRANSPARENT
                  cellIDs_[tx-1 + ( ty )*size_.x*3] =  2;           // THEN SET LEFT TO TRANSPARENT
                  lastlyLit_.push_back(sf::Vector2i(tx-1, ty));
            }

            if (  cellIDs_[tx-1 + (ty-1)*size_.x*3] == 2            // IF TOP LEFT
               && cellIDs_[tx+1 + (ty-1)*size_.x*3] == 2) {         // AND TOP RIGHT ARE TRANSPARENT
                  cellIDs_[ tx  + (ty-1)*size_.x*3] =  2;           // THEN SET TOP TO TRANSPARENT
                  lastlyLit_.push_back(sf::Vector2i(tx, ty-1));
            }

            if (  cellIDs_[tx+1 + (ty+1)*size_.x*3] == 2            // IF BOTTOM RIGHT
               && cellIDs_[tx+1 + (ty-1)*size_.x*3] == 2) {         // AND TOP RIGHT ARE TRANSPARENT
                  cellIDs_[tx+1 + ( ty )*size_.x*3] =  2;           // THEN SET RIGHT TO TRANSPARENT
                  lastlyLit_.push_back(sf::Vector2i(tx+1, ty));
            }

            if (  cellIDs_[tx+1 + (ty+1)*size_.x*3] == 2            // IF BOTTOM RIGHT
               && cellIDs_[tx-1 + (ty+1)*size_.x*3] == 2) {         // AND BOTTOM LEFT ARE TRANSPARENT
                  cellIDs_[ tx  + (ty+1)*size_.x*3] =  2;           // THEN SET BOTTOM TO TRANSPARENT
                  lastlyLit_.push_back(sf::Vector2i(tx, ty+1));
            }
        }
    }

    void ShadowMap::darken() {
        for (unsigned i=0; i<lastlyLit_.size(); ++i) {
            cellIDs_[lastlyLit_[i].x + lastlyLit_[i].y*size_.x*3] = 1;
        }
        lastlyLit_.clear();
    }

    void ShadowMap::update() {
        for (int x=0; x<3*size_.x; ++x) {
            for (int y=0; y<3*size_.y; ++y) {
                if      (  cellIDs_[x + y*3*size_.x] == 1
                         ) shadowImage_.setPixel(x, y, sf::Color(0, 0, 0, 200));
                else if (  cellIDs_[x + y*3*size_.x] == 2
                         ) shadowImage_.setPixel(x, y, sf::Color(0, 0, 0,   0));
            }
        }

        shadowTexture_.update(shadowImage_);
    }

    std::ifstream& ShadowMap::operator<<(std::ifstream& file) {
        try {
            for (int x=0; x<size_.x; ++x) {
                for (int y=0; y<size_.y; ++y) {
                    readFile <bool> (file, discovered_[x + y*size_.x]);
                    if (  discovered_[x + y*size_.x]
                        ) setLit(x, y);
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
