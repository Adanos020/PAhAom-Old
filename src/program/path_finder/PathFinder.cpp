/**
 * @file src/program/path_finder/PathFinder.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <list>

#include "PathFinder.hpp"

namespace rr {

    std::vector<sf::Vector2i> PathFinder::aStar(sf::Vector2i from, sf::Vector2i to, int tiles[]) {
        std::vector<sf::Vector2i>     path;
        std::list  <Point*>           opened;
        std::list  <Point*>           closed;

        Point* start = getPoint(tiles, from);
        Point* end   = getPoint(tiles, to);
        Point* current;
        Point* child;

        unsigned n = 0;

        start->setOpened(true);
        opened.push_back(start);

        while (n == 0 || (current != end)) {
            for (auto it=opened.begin(); it!=opened.end(); ++it) {
                if (  it == opened.begin() || (*it)->getF() <= current->getF()
                    ) current = *it;
            }

            if (  current == end
                ) break;

            opened.remove(current);
            current->setOpened(false);

            closed.push_back(current);
            current->setClosed(true);

            for (int x=-1; x<2; ++x) {
                for (int y=-1; y<2; ++y) {
                    if (  x == 0
                       && y == 0
                        ) continue;
                    
                    child = getPoint(tiles, sf::Vector2i(current->getPosition().x+x, current->getPosition().y+y));
                    if (   child->isClosed()
                       || !child->isWalkable()
                        ) continue;

                    if (x != 0 && y != 0) {
                        if (  !getPoint(tiles, sf::Vector2i(current->getPosition().x, current->getPosition().y + y))->isWalkable()
                           || !getPoint(tiles, sf::Vector2i(current->getPosition().x + x, current->getPosition().y))->isWalkable()
                            ) continue;
                    }

                    if (child->isOpened()) {
                        if (child->getG() > child->getG(current)) {
                            child->setParent(current);
                            child->calculateScores(end);
                        }
                    }
                    else {
                        child->setOpened(true);
                        opened.push_back(child);
                        
                        child->setParent(current);
                        child->calculateScores(end);
                    }
                }
            }

            ++n;
        }

        for (auto it=opened.begin(); it!=opened.end(); ++it) {
            (*it)->setOpened(false);
        }
        for (auto it=closed.begin(); it!=closed.end(); ++it) {
            (*it)->setClosed(false);
        }

        while (current->getParent() != nullptr && current != start) {
            path.push_back((sf::Vector2i) current->getPosition());
            current = current->getParent();
            ++n;
        }

        return path;
    }

}
