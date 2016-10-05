/**
 * @file src/game/PathFinder.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

namespace rr
{

    class PathFinder
    {
    private: class Node : public sf::Vector2i
             {
             private: Node*        m_parent;

                      bool         m_walkable;
                      bool         m_closed;
                      bool         m_open;

                      int          m_FScore;
                      int          m_GScore;
                      int          m_HScore;

             public:  bool isWalkable() const;
                      bool isOpen    () const;
                      bool isClosed  () const;

                      Node* getParent() const;

                      int getFScore(     ) const;
                      int getGScore(     ) const;
                      int getGScore(Node*) const;
                      int getHScore(     ) const;
                      int getHScore(Node*) const;

                      void calculateScores(Node*);

                      void setWalkable(bool);
                      void setOpen    (bool);
                      void setClosed  (bool);

                      void setParent(Node*);

                      bool operator==(Node&);
                      bool operator!=(Node&);

                      Node();
                      Node(int grid[], sf::Vector2i);
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates and returns a new node.
             ////////////////////////////////////////////////////////////////////////
             static Node* getNode(int tiles[], sf::Vector2i position);
    
    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Creates and returns a new node.
             ////////////////////////////////////////////////////////////////////////
             static std::vector<sf::Vector2i> aStar(sf::Vector2i from, sf::Vector2i to, int tiles[]);
    };

}

#endif // PATHFINDER_HPP
