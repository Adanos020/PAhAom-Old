/**
 * @file src/program/path_finder/PathFinder_Node.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "PathFinder.hpp"

namespace rr
{

    PathFinder::Node::Node() :
      m_parent  (nullptr),
      m_closed  (false),
      m_open    (false),
      m_position(sf::Vector2i(0, 0)),
      m_f       (0),
      m_g       (0),
      m_h       (0) {}

    PathFinder::Node::Node(sf::Vector2i position, bool walkable) :
      m_parent  (nullptr),
      m_closed  (false),
      m_open    (false),
      m_walkable(walkable),
      m_position(position),
      m_f       (0),
      m_g       (0),
      m_h       (0) {}

    void
    PathFinder::Node::calculateScores(PathFinder::Node* goal)
    {
        m_g = getG(m_parent);
        m_h = getH(goal);
        m_f = m_g + m_h;
    }

}
