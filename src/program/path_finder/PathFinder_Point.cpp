/**
 * @file src/program/path_finder/PathFinder_Point.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "PathFinder.hpp"

namespace rr {

    PathFinder::Point::Point() {
        parent_ = nullptr;
        
        closed_ = false;
        opened_ = false;
        
        fScore_ = 0;
        gScore_ = 0;
        hScore_ = 0;
        
        position_ = sf::Vector2i(0, 0);
    }

    PathFinder::Point::Point(sf::Vector2i position, bool walkable) {
        parent_ = nullptr;
        
        closed_ = false;
        opened_ = false;
        
        fScore_ = 0;
        gScore_ = 0;
        hScore_ = 0;

        walkable_ = walkable;
        position_ = position;
    }

    void PathFinder::Point::calculateScores(PathFinder::Point* goal) {
        gScore_ = getG(parent_);
        hScore_ = getH(goal);
        fScore_ = gScore_ + hScore_;
    }

}
