/**
 * @file src/program/game/FOV.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <cmath>
#include <iostream>

#include "FOV.hpp"

namespace rr
{
    
    void
    FOV::compute(ShadowMap& shadows, Level& level, sf::Vector2i origin, int range)
    {
        shadows.darken();
        shadows.setLit(origin.x, origin.y);
        for (unsigned octant = 0; octant < 8; octant++)
        {
            compute(shadows, level, octant, origin, 2*range, 1, Slope(1, 1), Slope(0, 1));
        }
        shadows.update();
    }

    void
    FOV::compute(ShadowMap& shadows, Level& level, unsigned octant, sf::Vector2i origin, int range, unsigned x, Slope top, Slope bottom)
    {
        for (; x <= (unsigned) range; x++)
        {
            unsigned topY;
            if (top.x_ == 1)
                topY = x;
            else
            {
                topY = ((x*2-1)*top.y_+top.x_) / (top.x_*2);
                if (  blocksLight(level, x, topY, octant, origin)
                   && top >= Slope(topY*2+1, x*2)
                   && !blocksLight(level, x, topY+1, octant, origin)
                    ) ++topY;
                else
                {
                    unsigned ax = x*2;
                    if (blocksLight(level, x+1, topY+1, octant, origin))
                        ++ax;
                    if (top > Slope(topY*2+1, ax))
                        ++topY;
                }
            }

            unsigned bottomY;
            if (bottom.y_ == 0)
                bottomY = 0;
            else
            {
                bottomY = ((x*2-1)*bottom.y_+bottom.x_)/(bottom.x_*2);
                if (   bottom >= Slope(bottomY*2+1, x*2)
                   &&  blocksLight(level, x, bottomY, octant, origin) 
                   && !blocksLight(level, x, bottomY+1, octant, origin)
                    )  ++bottomY;
            }

            int wasOpaque = -1;
            for (unsigned y = topY; (int) y >= (int) bottomY;-- y)
            {
                if (range < 0 || getDistance((int) x, (int) y) <= range)
                {
                    bool isOpaque = blocksLight(level, x, y, octant, origin);
                    
                    if (  isOpaque 
                       || (  (  y != topY    || top    > Slope(y*4-1, x*4+1))
                          && (  y != bottomY || bottom < Slope(y*4+1, x*4-1))
                           )
                        ) setVisible(shadows, x, y, octant, origin);

                    if ((int) x != range)
                    {
                        if (isOpaque)
                        {
                            if (wasOpaque == 0)
                            {
                                unsigned nx = x*2, ny = y*2+1;
                                if (blocksLight(level, x, y+1, octant, origin))
                                    --nx;
                                if (top > Slope(ny, nx))
                                {
                                    if (y == bottomY)
                                    {
                                        bottom = Slope(ny, nx);
                                        break;
                                    }
                                    else compute(shadows, level, octant, origin, range, x+1, top, Slope(ny, nx));
                                }
                                else if (y == bottomY)
                                    return;
                            }
                            wasOpaque = 1;
                        }
                        else
                        {
                            if (wasOpaque > 0)
                            {
                                unsigned nx = x*2, ny = y*2+1;

                                if (blocksLight(level, x+1, y+1, octant, origin))
                                    ++nx;
                                if (bottom >= Slope(ny, nx))
                                    return;
                                top = Slope(ny, nx);
                            }
                            wasOpaque = 0;
                        }
                    }
                }
            }
            if (wasOpaque != 0)
                break;
        }
    }

    bool
    FOV::seesEntity(Level& level, Entity* e1, Entity* e2)
    {
        for (unsigned octant = 0; octant < 8; octant++)
        {
            if (seesEntity(level, octant, e1->getGridPosition(), e2->getGridPosition(), 14, 1, Slope(1, 1), Slope(0, 1)))
                return true;
        }
        return false;
    }

    bool
    FOV::seesEntity(Level& level, unsigned octant, sf::Vector2i origin, sf::Vector2i dest, int range, unsigned x, Slope top, Slope bottom)
    {
        for (; x <= (unsigned) range; ++x)
        {
            unsigned topY;
            if (top.x_ == 1)
                topY = x;
            else
            {
                topY = ((x*2-1)*top.y_+top.x_) / (top.x_*2);
                if (  blocksLight(level, x, topY, octant, origin)
                   && top >= Slope(topY*2+1, x*2)
                   && !blocksLight(level, x, topY+1, octant, origin)
                    ) ++topY;
                else
                {
                    unsigned ax = x*2;
                    if (blocksLight(level, x+1, topY+1, octant, origin))
                        ++ax;
                    if (top > Slope(topY*2+1, ax))
                        ++topY;
                }
            }

            unsigned bottomY;
            if (bottom.y_ == 0)
                bottomY = 0;
            else
            {
                bottomY = ((x*2-1)*bottom.y_+bottom.x_)/(bottom.x_*2);
                if (   bottom >= Slope(bottomY*2+1, x*2)
                   &&  blocksLight(level, x, bottomY, octant, origin) 
                   && !blocksLight(level, x, bottomY+1, octant, origin)
                    )  ++bottomY;
            }

            int wasOpaque = -1;
            for (unsigned y = topY; (int) y >= (int) bottomY;-- y)
            {
                if (range < 0 || getDistance((int) x, (int) y) <= range)
                {
                    bool isOpaque = blocksLight(level, x, y, octant, origin);
                    
                    if (isOpaque || ((y != topY || top > Slope(y*4-1, x*4+1)) && (y != bottomY || bottom < Slope(y*4+1, x*4-1))))
                    {
                        if (getVisible(x, y, octant, origin) == dest)
                            return true;
                    }

                    if ((int) x != range)
                    {
                        if (isOpaque)
                        {
                            if (wasOpaque == 0)
                            {
                                unsigned nx = x*2, ny = y*2+1;
                                if (blocksLight(level, x, y+1, octant, origin))
                                    --nx;
                                if (top > Slope(ny, nx))
                                {
                                    if (y == bottomY)
                                    {
                                        bottom = Slope(ny, nx);
                                        break;
                                    }
                                    else seesEntity(level, octant, origin, dest, range, x+1, top, Slope(ny, nx));
                                }
                                else if (y == bottomY)
                                    return false;
                            }
                            wasOpaque = 1;
                        }
                        else
                        {
                            if (wasOpaque > 0)
                            {
                                unsigned nx = x*2, ny = y*2+1;

                                if (blocksLight(level, x+1, y+1, octant, origin))
                                    ++nx;
                                if (bottom >= Slope(ny, nx))
                                    return false;
                                top = Slope(ny, nx);
                            }
                            wasOpaque = 0;
                        }
                    }
                }
            }
            if (wasOpaque != 0)
                break;
        }

        return false;
    }

    bool
    FOV::blocksLight(Level& level, int x, int y, unsigned octant, sf::Vector2i origin)
    {
        int nx = origin.x, ny = origin.y;
        switch (octant)
        {
            case 0: nx += x; ny -= y; break;
            case 1: nx += y; ny -= x; break;
            case 2: nx -= y; ny -= x; break;
            case 3: nx -= x; ny -= y; break;
            case 4: nx -= x; ny += y; break;
            case 5: nx -= y; ny += x; break;
            case 6: nx += y; ny += x; break;
            case 7: nx += x; ny += y; break;
        }
        auto entity = level.getEntityAt(sf::Vector2i(nx, ny));
        bool doorClosed = entity != nullptr && instanceof <Door, Entity> (entity) && !((Door*) entity)->isOpen();

        return (nx < 77 && ny < 43) && (level.getTiles()[nx + ny*77] == 1 || doorClosed);
    }

    void
    FOV::setVisible(ShadowMap& shadows, int x, int y, unsigned octant, sf::Vector2i origin)
    {
        int nx = origin.x, ny = origin.y;
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
        shadows.setLit(nx, ny);
    }

    sf::Vector2i
    FOV::getVisible(int x, int y, unsigned octant, sf::Vector2i origin)
    {
        int nx = origin.x, ny = origin.y;
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
        return sf::Vector2i(nx, ny);
    }

    int
    FOV::getDistance(int x, int y)
    {
        if (x == 0) return y;
        if (y == 0) return x;

        return (int) sqrt(x*x + y*y);
    }

}
