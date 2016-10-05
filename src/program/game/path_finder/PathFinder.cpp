/**
 * @file src/program/game/path_finder/PathFinder.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <vector>
#include <algorithm>

#include "../PathFinder.hpp"

namespace rr
{

    std::vector <sf::Vector2i>
    PathFinder::aStar(sf::Vector2i from, sf::Vector2i to, int grid[])
    {
        std::vector <sf::Vector2i> path;

        std::vector <Node*> openList;
        std::vector <Node*> closedList;

        auto begin = new Node(grid, from);
        auto end   = new Node(grid, to  );
        
        Node* current = nullptr;
        Node* child   = nullptr;

        int tries = 0;

        // adding the point A to the open list
        begin->setOpen(true);
        openList.push_back(begin);

        while (tries == 0 || (*current != *end && tries <= 77*430))
        {
            if (openList.empty())
                return path;

            for (auto it = openList.begin(); it != openList.end(); ++it)
            {
                // picking an open node with the smallest F score
                if (it == openList.begin() || (*it)->getFScore() <= current->getFScore())
                {
                    current = *it;
                }
            }

            if (*current == *end)
                break;

            // the current node is now checked so it can be marked as closed
            current->setOpen(false);
            openList.erase(std::find(openList.begin(), openList.end(), current));

            current->setClosed(true);
            closedList.push_back(current);

            // checking all of the nodes surrounding the current one
            for (int y = -1; y <= 1; ++y)
            {
                if (grid[current->x + (current->y+y)*77] == 0
                 || grid[current->x + (current->y+y)*77] == 1
                 || grid[current->x + (current->y+y)*77] == 4)
                    continue;
                for (int x = -1; x <= 1; ++x)
                {
                    if (grid[current->x+x + current->y*77] == 0
                     || grid[current->x+x + current->y*77] == 1
                     || grid[current->x+x + current->y*77] == 4)
                        continue;
                    if (x != 0 || y != 0) // ignoring the node in the middle, because this is the current node
                    {
                        bool exists = false;
                        for (auto it = openList.begin(); it != openList.end(); ++it)
                        {
                            if ((*it)->x == current->x+x && (*it)->y == current->y+y)
                            {
                                child = *it;
                                exists = true;
                                break;
                            }
                        }
                        if (!exists)
                        for (auto it = closedList.begin(); it != closedList.end(); ++it)
                        {
                            if ((*it)->x == current->x+x && (*it)->y == current->y+y)
                            {
                                child = *it;
                                exists = true;
                                break;
                            }
                        }
                        if (!exists)
                            child = new Node(grid, sf::Vector2i(current->x + x, current->y + y));

                        if (child->isWalkable() && !child->isClosed())
                        {
                            if (child->isOpen()) // if the node is already marked as open
                            {
                                if (child->getGScore() > child->getGScore(current)) // checking if it is better to walk through
                                {                                                   // the current node
                                    child->setParent(current);
                                    child->calculateScores(end);
                                }
                            }
                            else // if the child node is not marked as open
                            {
                                child->setParent(current);   // then connect it to the current node,
                                child->setOpen(true);        // set it open
                                child->calculateScores(end); // and calculate its scores

                                openList.push_back(child);
                            }
                        }
                        else if (!exists)
                            delete child;
                    }
                }
            }
            ++tries;
        }

        for (auto it = openList.begin(); it != openList.end(); ++it)
        {
            (*it)->setOpen(false);
        }
        for (auto it = closedList.begin(); it != closedList.end(); ++it)
        {
            (*it)->setClosed(false);
        }

        while (current->getParent() != nullptr && *current != *begin)
        {
            path.push_back(sf::Vector2i(current->x, current->y));
            
            auto temp = current;
            current = temp->getParent();
            delete temp;
        }

        openList.clear();
        closedList.clear();

        return path;
    }

}
