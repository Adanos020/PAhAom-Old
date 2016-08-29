/**
 * @file src/program/path_finder/PathFinder_Node.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "PathFinder.hpp"

namespace rr
{

    PathFinder::Node::Node() :
      parent_  (nullptr),
      closed_  (false),
      opened_  (false),
      position_(sf::Vector2i(0, 0)),
      f_       (0),
      g_       (0),
      h_       (0) {}

    PathFinder::Node::Node(sf::Vector2i position, bool walkable) :
      parent_  (nullptr),
      closed_  (false),
      opened_  (false),
      walkable_(walkable),
      position_(position),
      f_       (0),
      g_       (0),
      h_       (0) {}

    void
    PathFinder::Node::calculateScores(PathFinder::Node* goal)
    {
        g_ = getG(parent_);
        h_ = getH(goal);
        f_ = g_ + h_;
    }

}
