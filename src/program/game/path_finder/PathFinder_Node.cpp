/**
 * @file src/program/game/path_finder/PathFinder_Node.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../PathFinder.hpp"

namespace rr
{

    PathFinder::Node::Node() :
      m_parent  (nullptr),
      m_walkable(false),
      m_closed  (false),
      m_open    (false),
      m_FScore  (0),
      m_GScore  (0),
      m_HScore  (0) {}

    PathFinder::Node::Node(int grid[], sf::Vector2i position) :
      m_parent  (nullptr),
      m_walkable(grid[position.x + position.y*77] != 0
              && grid[position.x + position.y*77] != 1
              && grid[position.x + position.y*77] != 5),
      m_closed  (false),
      m_open    (false),
      m_FScore  (0),
      m_GScore  (0),
      m_HScore  (0)
    {
        this->x = position.x;
        this->y = position.y;
    }

    bool
    PathFinder::Node::isWalkable() const
    {
        return m_walkable;
    }

    bool
    PathFinder::Node::isOpen() const
    {
        return m_open;
    }

    bool
    PathFinder::Node::isClosed() const
    {
        return m_closed;
    }

    PathFinder::Node*
    PathFinder::Node::getParent() const
    {
        return m_parent;
    }

    int
    PathFinder::Node::getFScore() const
    {
        return m_FScore;
    }

    int
    PathFinder::Node::getGScore() const
    {
        return m_GScore;
    }

    int
    PathFinder::Node::getGScore(PathFinder::Node* neighbor) const
    {
        return neighbor->getGScore() + ((this->x == neighbor->x || this->y == neighbor->y) ? 10 : 14);
    }

    int
    PathFinder::Node::getHScore() const
    {
        return m_HScore;
    }

    int
    PathFinder::Node::getHScore(PathFinder::Node* other) const
    {
        return 10 * (std::abs(this->x - other->x) + std::abs(this->y - other->y));
    }

    void
    PathFinder::Node::calculateScores(PathFinder::Node* goal)
    {
        m_GScore = getGScore(m_parent);
        m_HScore = getHScore(goal);
        m_FScore = m_GScore + m_HScore;
    }

    void
    PathFinder::Node::setWalkable(bool b)
    {
        m_walkable = b;
    }

    void
    PathFinder::Node::setOpen(bool b)
    {
        m_open = b;
    }

    void
    PathFinder::Node::setClosed(bool b)
    {
        m_closed = b;
    }

    void
    PathFinder::Node::setParent(Node* parent)
    {
        m_parent = parent;
    }

    bool
    PathFinder::Node::operator==(PathFinder::Node& right)
    {
        return x == right.x && y == right.y;
    }

    bool
    PathFinder::Node::operator!=(PathFinder::Node& right)
    {
        return x != right.x || y != right.y;
    }

}
