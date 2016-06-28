/**
 * @file src/program/game/fov/fov_FOV.cpp
 * @author Adam 'Adanos' G�sior
 * Used library: SFML 2.3.2
 */

#include "fov.hpp"

#include <cmath>
#include <iostream>

namespace rr {

    FOV::FOV(Mask masks[], int tiles[])
    : masks_ (masks),
      tiles_ (tiles) {}

    void FOV::compute(sf::Vector2u origin, int range) {
        masks_[origin.x+origin.y*77].see(true);
        for (unsigned octant = 0; octant < 8; octant++) {
            compute(octant, origin, 2*range, 1, Slope(1, 1), Slope(0, 1));
        }
        smoothShade();
    }

    void FOV::compute(unsigned octant, sf::Vector2u origin, int range, unsigned x, Slope top, Slope bottom) {
        for (; x <= (unsigned)range; x++) {
            unsigned topY;
            if (  top.x_ == 1
                ) topY = x;
            else {
                topY = ((x*2-1)*top.y_+top.x_) / (top.x_*2);
                if (  blocksLight(x, topY, octant, origin) && top >= Slope(topY*2+1, x*2) && !blocksLight(x, topY+1, octant, origin)
                    ) topY++;
                else {
                    unsigned ax = x*2;
                    if (  blocksLight(x+1, topY+1, octant, origin)
                        ) ax++;
                    if (  top > Slope(topY*2+1, ax)
                        ) topY++;
                }
            }

            unsigned bottomY;
            if (  bottom.y_ == 0
                ) bottomY = 0;
            else {
                bottomY = ((x*2-1)*bottom.y_+bottom.x_)/(bottom.x_*2);
                if (  bottom >= Slope(bottomY*2+1, x*2) && blocksLight(x, bottomY, octant, origin) && !blocksLight(x, bottomY+1, octant, origin)
                    ) bottomY++;
            }

            int wasOpaque = -1;
            for (unsigned y = topY; (int)y >= (int)bottomY; y--) {
                if (range < 0 || getDistance((int)x, (int)y) <= range) {
                    bool isOpaque  = blocksLight(x, y, octant, origin);
                    bool isVisible = isOpaque || ((y != topY || top > Slope(y*4-1, x*4+1)) && (y != bottomY || bottom < Slope(y*4+1, x*4-1)));
                    if (  isVisible
                        ) setVisible(x, y, octant, origin);

                    if ((int)x != range) {
                        if (isOpaque) {
                            if (wasOpaque == 0) {
                                unsigned nx = x*2, ny = y*2+1;
                                if (  blocksLight(x, y+1, octant, origin)
                                    ) nx--;
                                if (top > Slope(ny, nx)) {
                                    if (y == bottomY) {
                                        bottom = Slope(ny, nx);
                                        break;
                                    }
                                    else
                                        compute(octant, origin, range, x+1, top, Slope(ny, nx));
                                }
                                else if (  y == bottomY
                                         ) return;
                            }
                            wasOpaque = 1;
                        }
                        else {
                            if (wasOpaque > 0) {
                                unsigned nx = x*2, ny = y*2+1;

                                if (  blocksLight(x+1, y+1, octant, origin)
                                    ) nx++;
                                if (  bottom >= Slope(ny, nx)
                                    ) return;
                                top = Slope(ny, nx);
                            }
                            wasOpaque = 0;
                        }
                    }
                }
            }
            if (  wasOpaque != 0
                ) break;
        }
    }

    bool FOV::blocksLight(unsigned x, unsigned y, unsigned octant, sf::Vector2u origin) {
        unsigned nx = origin.x, ny = origin.y;
        switch (octant) {
            case 0: nx += x; ny -= y; break;
            case 1: nx += y; ny -= x; break;
            case 2: nx -= y; ny -= x; break;
            case 3: nx -= x; ny -= y; break;
            case 4: nx -= x; ny += y; break;
            case 5: nx -= y; ny += x; break;
            case 6: nx += y; ny += x; break;
            case 7: nx += x; ny += y; break;
        }
        return (nx < 77 && ny < 43) && (tiles_[nx+ny*77] == 1 || tiles_[nx+ny*77] == 4);
    }

    void FOV::setVisible(unsigned x, unsigned y, unsigned octant, sf::Vector2u origin) {
        unsigned nx = origin.x, ny = origin.y;
        switch (octant) {
            case 0: nx += x; ny -= y; break;
            case 1: nx += y; ny -= x; break;
            case 2: nx -= y; ny -= x; break;
            case 3: nx -= x; ny -= y; break;
            case 4: nx -= x; ny += y; break;
            case 5: nx -= y; ny += x; break;
            case 6: nx += y; ny += x; break;
            case 7: nx += x; ny += y; break;
        }
        masks_[nx + ny*77].see(true);
    }

    int FOV::getDistance(int x, int y) {
        if (  x == 0
            ) return y;
        if (  y == 0
            ) return x;

        return (int)sqrt(x*x + y*y);
    }

    void FOV::smoothShade() {
        for (int i=0; i<77; i++) {
            for (int j=0; j<43; j++) {
                sf::Color shades[4] = sf::Color(0, 0, 0, 160);
                if (i > 0 && i < 76 && j > 0 && j < 42) {           // is not on border
                    if (masks_[i + j*77].isSeen()) {                // current tile is seen
                        if (  masks_[i-1 + (j-1)*77].isSeen()       // top left is seen
                            ) shades[0] = sf::Color::Transparent;
                        if (  masks_[i+1 + (j-1)*77].isSeen()       // top right is seen
                            ) shades[1] = sf::Color::Transparent;
                        if (  masks_[i+1 + (j+1)*77].isSeen()       // bottom right is seen
                            ) shades[2] = sf::Color::Transparent;
                        if (  masks_[i-1 + (j+1)*77].isSeen()       // bottom left is seen
                            ) shades[3] = sf::Color::Transparent;

                        if (masks_[i-1 + j*77].isSeen()) {          // left is seen
                            shades[0] = sf::Color::Transparent;
                            shades[3] = sf::Color::Transparent;
                        }
                        if (masks_[i+1 + j*77].isSeen()) {          // right is seen
                            shades[1] = sf::Color::Transparent;
                            shades[2] = sf::Color::Transparent;
                        }
                        if (masks_[i + (j-1)*77].isSeen()) {        // top is seen
                            shades[0] = sf::Color::Transparent;
                            shades[1] = sf::Color::Transparent;
                        }
                        if (masks_[i + (j+1)*77].isSeen()) {        // bottom is seen
                            shades[3] = sf::Color::Transparent;
                            shades[2] = sf::Color::Transparent;
                        }

                        if (!masks_[i-1 + j*77].isSeen()) {         // left is not seen
                            shades[0] = sf::Color(0, 0, 0, 160);
                            shades[3] = sf::Color(0, 0, 0, 160);
                        }
                        if (!masks_[i+1 + j*77].isSeen()) {         // right is not seen
                            shades[1] = sf::Color(0, 0, 0, 160);
                            shades[2] = sf::Color(0, 0, 0, 160);
                        }
                        if (!masks_[i + (j-1)*77].isSeen()) {       // top is not seen
                            shades[0] = sf::Color(0, 0, 0, 160);
                            shades[1] = sf::Color(0, 0, 0, 160);
                        }
                        if (!masks_[i + (j+1)*77].isSeen()) {       // bottom is not seen
                            shades[2] = sf::Color(0, 0, 0, 160);
                            shades[3] = sf::Color(0, 0, 0, 160);
                        }

                        if ( !masks_[i-1 + (j-1)*77].isSeen()       // top left is not seen
                            ) shades[0] = sf::Color(0, 0, 0, 160);
                        if ( !masks_[i+1 + (j-1)*77].isSeen()       // top right is not seen
                            ) shades[1] = sf::Color(0, 0, 0, 160);
                        if ( !masks_[i+1 + (j+1)*77].isSeen()       // bottom right is not seen
                            ) shades[2] = sf::Color(0, 0, 0, 160);
                        if ( !masks_[i-1 + (j+1)*77].isSeen()       // bottom left is not seen
                            ) shades[3] = sf::Color(0, 0, 0, 160);

                        if ( !masks_[i-1 + (j-1)*77].isDiscovered() // top left was never seen
                            ) shades[0] = sf::Color::Black;
                        if ( !masks_[i+1 + (j-1)*77].isDiscovered() // top right was never seen
                            ) shades[1] = sf::Color::Black;
                        if ( !masks_[i+1 + (j+1)*77].isDiscovered() // bottom right was never seen
                            ) shades[2] = sf::Color::Black;
                        if ( !masks_[i-1 + (j+1)*77].isDiscovered() // bottom left was never seen
                            ) shades[3] = sf::Color::Black;

                        if (!masks_[i-1 + j*77].isDiscovered()) {   // left was never seen
                            shades[0] = sf::Color::Black;
                            shades[3] = sf::Color::Black;
                        }
                        if (!masks_[i+1 + j*77].isDiscovered()) {   // right was never seen
                            shades[1] = sf::Color::Black;
                            shades[2] = sf::Color::Black;
                        }
                        if (!masks_[i + (j-1)*77].isDiscovered()) { // top was never seen
                            shades[0] = sf::Color::Black;
                            shades[1] = sf::Color::Black;
                        }
                        if (!masks_[i + (j+1)*77].isDiscovered()) { // bottom was never seen
                            shades[2] = sf::Color::Black;
                            shades[3] = sf::Color::Black;
                        }

                        masks_[i + j*77].setFadeOut(shades);
                    }
                    else if (masks_[i + j*77].isDiscovered()) {     // current tile was seen
                        if (  masks_[i-1 + (j-1)*77].isDiscovered() // top left was seen
                            ) shades[0] = sf::Color(0, 0, 0, 160);
                        if (  masks_[i+1 + (j-1)*77].isDiscovered() // top right was seen
                            ) shades[1] = sf::Color(0, 0, 0, 160);
                        if (  masks_[i+1 + (j+1)*77].isDiscovered() // bottom right was seen
                            ) shades[2] = sf::Color(0, 0, 0, 160);
                        if (  masks_[i-1 + (j+1)*77].isDiscovered() // bottom left was seen
                            ) shades[3] = sf::Color(0, 0, 0, 160);

                        if (masks_[i-1 + j*77].isDiscovered()) {    // left was seen
                            shades[0] = sf::Color(0, 0, 0, 160);
                            shades[3] = sf::Color(0, 0, 0, 160);
                        }
                        if (masks_[i+1 + j*77].isDiscovered()) {    // right was seen
                            shades[1] = sf::Color(0, 0, 0, 160);
                            shades[2] = sf::Color(0, 0, 0, 160);
                        }
                        if (masks_[i + (j-1)*77].isDiscovered()) {  // top was seen
                            shades[0] = sf::Color(0, 0, 0, 160);
                            shades[1] = sf::Color(0, 0, 0, 160);
                        }
                        if (masks_[i + (j+1)*77].isDiscovered()) {  // bottom was seen
                            shades[2] = sf::Color(0, 0, 0, 160);
                            shades[3] = sf::Color(0, 0, 0, 160);
                        }

                        if (!masks_[i-1 + j*77].isDiscovered()) {   // left was never seen
                            shades[0] = sf::Color::Black;
                            shades[3] = sf::Color::Black;
                        }
                        if (!masks_[i+1 + j*77].isDiscovered()) {   // right was never seen
                            shades[1] = sf::Color::Black;
                            shades[2] = sf::Color::Black;
                        }
                        if (!masks_[i + (j-1)*77].isDiscovered()) { // top was never seen
                            shades[0] = sf::Color::Black;
                            shades[1] = sf::Color::Black;
                        }
                        if (!masks_[i + (j+1)*77].isDiscovered()) { // bottom was never seen
                            shades[2] = sf::Color::Black;
                            shades[3] = sf::Color::Black;
                        }

                        if ( !masks_[i-1 + (j-1)*77].isDiscovered() // top left was never seen
                            ) shades[0] = sf::Color::Black;
                        if ( !masks_[i+1 + (j-1)*77].isDiscovered() // top right was never seen
                            ) shades[1] = sf::Color::Black;
                        if ( !masks_[i+1 + (j+1)*77].isDiscovered() // bottom right was never seen
                            ) shades[2] = sf::Color::Black;
                        if ( !masks_[i-1 + (j+1)*77].isDiscovered() // bottom left was never seen
                            ) shades[3] = sf::Color::Black;

                        masks_[i + j*77].setFadeOut(shades);
                    }
                }
                else {                                              // is on border
                    for (int i=0; i<4; i++) {
                        shades[i] = sf::Color::Black;
                    }

                    if (masks_[i + j*77].isSeen()) {
                        if      (  i == 0  && j == 0                // top left corner
                                 ) shades[2] = sf::Color::Transparent;
                        else if (  i == 76 && j == 0                // top right corner
                                 ) shades[3] = sf::Color::Transparent;
                        else if (  i == 0  && j == 42               // bottom left corner
                                 ) shades[1] = sf::Color::Transparent;
                        else if (  i == 76 && j == 42               // bottom right corner
                                 ) shades[0] = sf::Color::Transparent;

                        else if (i == 0  && j > 0 && j < 42) {      // left edge
                            if (  masks_[i+1 + (j-1)*77].isSeen()       // top right
                                ) shades[1] = sf::Color::Transparent;
                            else
                                shades[1] = (masks_[i+1 + (j-1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i + (j-1)*77].isSeen()         // top
                                ) shades[1] = sf::Color::Transparent;
                            else
                                shades[1] = (masks_[i + (j-1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;
                            
                            if (  masks_[i+1 + (j+1)*77].isSeen()       // bottom right
                                ) shades[2] = sf::Color::Transparent;
                            else
                                shades[2] = (masks_[i+1 + (j+1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;
                            
                            if (  masks_[i + (j+1)*77].isSeen()         // bottom
                                ) shades[2] = sf::Color::Transparent;
                            else
                                shades[2] = (masks_[i + (j+1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;
                        }
                        else if (i == 76 && j > 0 && j < 42) {      // right edge
                            if (  masks_[i-1 + (j-1)*77].isSeen()       // top left
                                ) shades[0] = sf::Color::Transparent;
                            else
                                  shades[0] = (masks_[i+1 + (j-1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i + (j-1)*77].isSeen()         // top
                                ) shades[0] = sf::Color::Transparent;
                            else
                                  shades[0] = (masks_[i + (j-1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i-1 + (j+1)*77].isSeen()       // bottom right
                                ) shades[3] = sf::Color::Transparent;
                            else
                                  shades[3] = (masks_[i+1 + (j+1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i + (j+1)*77].isSeen()         // bottom
                                ) shades[3] = sf::Color::Transparent;
                            else
                                  shades[3] = (masks_[i + (j+1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;
                        }
                        else if (j == 0  && i > 0 && i < 76) {      // top edge
                            if (  masks_[i+1 + (j+1)*77].isSeen()       // bottom right
                                ) shades[2] = sf::Color::Transparent;
                            else
                                  shades[2] = (masks_[i+1 + (j+1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i+1 + j*77].isSeen()           // right
                                ) shades[2] = sf::Color::Transparent;
                            else
                                  shades[2] = (masks_[i+1 + j*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i-1 + (j+1)*77].isSeen()       // bottom left
                                ) shades[3] = sf::Color::Transparent;
                            else
                                  shades[3] = (masks_[i-1 + (j+1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i-1 + j*77].isSeen()           // left
                                ) shades[3] = sf::Color::Transparent;
                            else
                                  shades[3] = (masks_[i-1 + j*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;
                        }
                        else if (j == 42 && i > 0 && i < 76) {      // bottom edge
                            if (  masks_[i+1 + (j-1)*77].isSeen()       // top right
                                ) shades[1] = sf::Color::Transparent;
                            else
                                  shades[1] = (masks_[i+1 + (j-1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i+1 + j*77].isSeen()           // right
                                ) shades[1] = sf::Color::Transparent;
                            else
                                  shades[1] = (masks_[i+1 + j*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i-1 + (j-1)*77].isSeen()       // top left
                                ) shades[0] = sf::Color::Transparent;
                            else
                                  shades[0] = (masks_[i-1 + (j-1)*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;

                            if (  masks_[i-1 + j*77].isSeen()           // left
                                ) shades[0] = sf::Color::Transparent;
                            else
                                  shades[0] = (masks_[i-1 + j*77].isDiscovered()) ? sf::Color(0, 0, 0, 160) : sf::Color::Black;
                        }

                        masks_[i + j*77].setFadeOut(shades);
                    }
                    else if (masks_[i + j*77].isDiscovered()) {
                        if      (  i == 0  && j == 0                // top left corner
                                 ) shades[2] = sf::Color(0, 0, 0, 160);
                        else if (  i == 76 && j == 0                // top right corner
                                 ) shades[3] = sf::Color(0, 0, 0, 160);
                        else if (  i == 0  && j == 42               // bottom left corner
                                 ) shades[1] = sf::Color(0, 0, 0, 160);
                        else if (  i == 76 && j == 42               // bottom right corner
                                 ) shades[0] = sf::Color(0, 0, 0, 160);

                        else if (i == 0  && j > 0 && j < 42) {       // left edge
                            if ( !masks_[i+1 + (j-1)*77].isDiscovered() // top right
                                ) shades[1] = sf::Color::Black;
                            else
                                  shades[1] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i + (j-1)*77].isDiscovered()   // top
                                ) shades[1] = sf::Color::Black;
                            else
                                  shades[1] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i+1 + (j+1)*77].isDiscovered() // bottom right
                                ) shades[2] = sf::Color::Black;
                            else
                                  shades[2] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i + (j+1)*77].isDiscovered()   // bottom
                                ) shades[2] = sf::Color::Black;
                            else
                                  shades[2] = sf::Color(0, 0, 0, 160);
                        }
                        else if (i == 76 && j > 0 && j < 42) {       // right edge
                            if ( !masks_[i-1 + (j-1)*77].isDiscovered() // top left
                                ) shades[0] = sf::Color::Black;
                            else
                                  shades[0] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i + (j-1)*77].isDiscovered()   // top
                                ) shades[0] = sf::Color::Black;
                            else
                                  shades[0] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i-1 + (j+1)*77].isDiscovered() // bottom left
                                ) shades[3] = sf::Color::Black;
                            else
                                  shades[3] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i + (j+1)*77].isDiscovered()   // bottom
                                ) shades[3] = sf::Color::Black;
                            else
                                  shades[3] = sf::Color(0, 0, 0, 160);
                        }
                        else if (j == 0  && i > 0 && i < 76) {       // top edge
                            if ( !masks_[i+1 + (j+1)*77].isDiscovered() // bottom right
                                ) shades[2] = sf::Color::Black;
                            else
                                  shades[2] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i+1 + j*77].isDiscovered()     // right
                                ) shades[2] = sf::Color::Black;
                            else
                                  shades[2] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i-1 + (j+1)*77].isDiscovered() // bottom left
                                ) shades[3] = sf::Color::Black;
                            else
                                  shades[3] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i-1 + j*77].isDiscovered()     // left
                                ) shades[3] = sf::Color::Black;
                            else
                                  shades[3] = sf::Color(0, 0, 0, 160);
                        }
                        else if (j == 42 && i > 0 && i < 76) {       // bottom edge
                            if ( !masks_[i+1 + (j-1)*77].isDiscovered() // top right
                                ) shades[1] = sf::Color::Black;
                            else
                                  shades[1] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i+1 + j*77].isDiscovered()     // right
                                ) shades[1] = sf::Color::Black;
                            else
                                  shades[1] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i-1 + (j-1)*77].isDiscovered() // top left
                                ) shades[0] = sf::Color::Black;
                            else
                                  shades[0] = sf::Color(0, 0, 0, 160);

                            if ( !masks_[i-1 + j*77].isDiscovered()     // left
                                ) shades[0] = sf::Color::Black;
                            else
                                  shades[0] = sf::Color(0, 0, 0, 160);
                        }

                        masks_[i + j*77].setFadeOut(shades);
                    }
                }
            }
        }
    }

}
