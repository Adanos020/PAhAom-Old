/**
 * @file src/program/path_finder/PathFinder.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <list>

#include "PathFinder.hpp"

namespace rr
{

    PathFinder::Node* PathFinder::getNode(int tiles[], sf::Vector2i position)
    {
        bool walkable = true;
        if (  tiles[position.x + 77*position.y] == 0
           || tiles[position.x + 77*position.y] == 1
            ) walkable = false;
        return new Node(position, walkable);
    }

    std::vector<sf::Vector2i>
    PathFinder::aStar(sf::Vector2i from, sf::Vector2i to, int tiles[])
    {
        std::vector <sf::Vector2i> path;
        std::list   <    Node*   > open;
        std::list   <    Node*   > closed;

        Node* start = getNode(tiles, from);
        Node* end   = getNode(tiles, to);
        Node* current;
        Node* child;

        unsigned n = 0;

        start->setOpen(true);
        open.push_back(start);

        while ((n == 0 || (current != end && n < 50)))
        {
            for (auto it = open.begin(); it != open.end(); ++it)
            {
                if (it == open.begin() || (*it)->getF() <= current->getF())
                    current = *it;
            }

            if (current == end)
                break;

            open.remove(current);
            current->setOpen(false);

            closed.push_back(current);
            current->setClosed(true);

            for (int x = -1; x <= 1; ++x)
            {
                for (int y = -1; y <= 1; ++y)
                {
                    if (x == 0 && y == 0)
                        continue;

                    child = getNode(tiles, sf::Vector2i(current->getPosition().x + x, current->getPosition().y + y));
                    if (child->isClosed() || !child->isWalkable())
                        continue;

                    if (x != 0 && y != 0)
                    {
                        if (  !getNode(tiles, sf::Vector2i(current->getPosition().x, current->getPosition().y + y))->isWalkable()
                           || !getNode(tiles, sf::Vector2i(current->getPosition().x + x, current->getPosition().y))->isWalkable()
                            ) continue;
                    }

                    if (child->isOpen())
                    {
                        if (child->getG() > child->getG(current))
                        {
                            child->setParent(current);
                            child->calculateScores(end);
                        }
                    }
                    else
                    {
                        child->setOpen(true);
                        open.push_back(child);
                        
                        child->setParent(current);
                        child->calculateScores(end);
                    }
                }
            }

            ++n;
        }

        for (auto it=open.begin(); it!=open.end(); ++it)
        {
            (*it)->setOpen(false);
        }
        for (auto it=closed.begin(); it!=closed.end(); ++it)
        {
            (*it)->setClosed(false);
        }

        while (current->getParent() != nullptr && current != start)
        {
            path.push_back((sf::Vector2i) current->getPosition());
            current = current->getParent();
            ++n;
        }

        open.clear();
        closed.clear();

        return path;
    }

}
