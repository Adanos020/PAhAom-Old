/**
 * @file src/program/path_finder/PathFinder.hpp
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
    private: class Node
             {
             private: Node*        m_parent;

                      bool         m_closed;
                      bool         m_open;
                      bool         m_walkable;

                      sf::Vector2i m_position;

                      int          m_f;
                      int          m_g;
                      int          m_h;

             public:  ////////////////////////////////////////////////////////////////////////
                      /// \brief Default constructor.
                      ////////////////////////////////////////////////////////////////////////
                      Node();

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Regular constructor.
                      ////////////////////////////////////////////////////////////////////////
                      Node(sf::Vector2i position, bool walkable);

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Calculates the F score, G score and H score with another
                      /// node.
                      ////////////////////////////////////////////////////////////////////////
                      void calculateScores(Node* goal);

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Sets the node's parent node.
                      ////////////////////////////////////////////////////////////////////////
                      void setParent(Node* n) { m_parent = n; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Sets the node closed.
                      ////////////////////////////////////////////////////////////////////////
                      void setClosed(bool closed) { m_closed = closed; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Sets the node open.
                      ////////////////////////////////////////////////////////////////////////
                      void setOpen(bool open) { m_open = open; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Sets the node walkable.
                      ////////////////////////////////////////////////////////////////////////
                      void setWalkable(bool walkable) { m_walkable = walkable; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Tells if the node is closed.
                      ////////////////////////////////////////////////////////////////////////
                      bool isClosed() const { return m_closed; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Tells if the node is open.
                      ////////////////////////////////////////////////////////////////////////
                      bool isOpen() const { return m_open; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Tells if the node is walkable.
                      ////////////////////////////////////////////////////////////////////////
                      bool isWalkable() const { return m_walkable; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's position as two integers.
                      ////////////////////////////////////////////////////////////////////////
                      sf::Vector2i getPosition() const { return m_position; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's position as two floats.
                      ////////////////////////////////////////////////////////////////////////
                      sf::Vector2f getFPosition() const { return (sf::Vector2f) m_position; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's parent node.
                      ////////////////////////////////////////////////////////////////////////
                      Node* getParent() const { return m_parent; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's F score.
                      ////////////////////////////////////////////////////////////////////////
                      int getF() const { return m_f; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's G score.
                      ////////////////////////////////////////////////////////////////////////
                      int getG() const { return m_g; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Calculates and returns the node's F score.
                      ////////////////////////////////////////////////////////////////////////
                      int getG(Node* n) const { return n->m_g + ((m_position.x == n->m_position.x || m_position.y == n->m_position.y) ? 10 : 14); }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's H score.
                      ////////////////////////////////////////////////////////////////////////
                      int getH() const { return m_h; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Calculates and returns the node's H score.
                      ////////////////////////////////////////////////////////////////////////
                      int getH(Node* n)  const { return (std::abs(n->m_position.x - m_position.x) + std::abs(n->m_position.y - m_position.y))*10; }
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
