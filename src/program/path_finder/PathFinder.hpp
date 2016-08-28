/**
 * @file src/program/path_finder/PathFinder.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
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
             private: Node*        parent_;

                      bool         closed_;
                      bool         opened_;
                      bool         walkable_;

                      sf::Vector2i position_;

                      int          f_;
                      int          g_;
                      int          h_;

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
                      void setParent(Node* n) { parent_   = n; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Sets the node closed.
                      ////////////////////////////////////////////////////////////////////////
                      void setClosed(bool closed) { closed_   = closed; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Sets the node opened.
                      ////////////////////////////////////////////////////////////////////////
                      void setOpened(bool opened) { opened_   = opened; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Sets the node walkable.
                      ////////////////////////////////////////////////////////////////////////
                      void setWalkable(bool walkable) { walkable_ = walkable; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Tells if the node is closed.
                      ////////////////////////////////////////////////////////////////////////
                      bool isClosed() const { return closed_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Tells if the node is opened.
                      ////////////////////////////////////////////////////////////////////////
                      bool isOpened() const { return opened_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Tells if the node is walkable.
                      ////////////////////////////////////////////////////////////////////////
                      bool isWalkable() const { return walkable_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's position as two integers.
                      ////////////////////////////////////////////////////////////////////////
                      sf::Vector2i getPosition() const { return position_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's position as two floats.
                      ////////////////////////////////////////////////////////////////////////
                      sf::Vector2f getFPosition() const { return (sf::Vector2f) position_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's parent node.
                      ////////////////////////////////////////////////////////////////////////
                      Node* getParent() const { return parent_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's F score.
                      ////////////////////////////////////////////////////////////////////////
                      int getF() const { return f_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's G score.
                      ////////////////////////////////////////////////////////////////////////
                      int getG() const { return g_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Calculates and returns the node's F score.
                      ////////////////////////////////////////////////////////////////////////
                      int getG(Node* n) const { return n->g_+((position_.x == n->position_.x || position_.y == n->position_.y) ? 10 : 14); }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Returns the node's H score.
                      ////////////////////////////////////////////////////////////////////////
                      int getH() const { return h_; }

                      ////////////////////////////////////////////////////////////////////////
                      /// \brief Calculates and returns the node's H score.
                      ////////////////////////////////////////////////////////////////////////
                      int getH(Node* n)  const { return (std::abs(n->position_.x - position_.x) + std::abs(n->position_.y - position_.y))*10; }
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates and returns a new node.
             ////////////////////////////////////////////////////////////////////////
             static Node* getNode (int tiles[], sf::Vector2i position)
             {
                 bool walkable = true;
                 if (  tiles[position.x + 77*position.y] == 0
                    || tiles[position.x + 77*position.y] == 1
                     ) walkable = false;
                 return new Node(position, walkable);
             }
    
    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Creates and returns a new node.
             ////////////////////////////////////////////////////////////////////////
             static std::vector<sf::Vector2i> aStar(sf::Vector2i from, sf::Vector2i to, int tiles[]);
    };

}

#endif // PATHFINDER_HPP
