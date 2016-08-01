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

namespace rr {

    class PathFinder {
    private: class Node {
             private: Node*        parent_;

                      bool         closed_;
                      bool         opened_;
                      bool         walkable_;

                      sf::Vector2i position_;

                      int          f_;
                      int          g_;
                      int          h_;
             
             public:  Node();
                      Node(sf::Vector2i position, bool walkable);

                      void         calculateScores(Node* goal);

                      void         setParent      (Node* n)        { parent_   = n; }
                      void         setClosed      (bool closed)    { closed_   = closed; }
                      void         setOpened      (bool opened)    { opened_   = opened; }
                      void         setWalkable    (bool walkable)  { walkable_ = walkable; }

                      bool         isClosed       ()         const { return closed_; }
                      bool         isOpened       ()         const { return opened_; }
                      bool         isWalkable     ()         const { return walkable_; }

                      sf::Vector2i getPosition    ()         const { return position_; }
                      sf::Vector2f getFPosition   ()         const { return (sf::Vector2f) position_; }

                      Node*        getParent      ()         const { return parent_; }

                      int          getF	          ()         const { return f_; }
                      int          getG	          ()         const { return g_; }
                      int          getG	          (Node* n)  const { return n->g_+((position_.x == n->position_.x || position_.y == n->position_.y) ? 10 : 14); }
                      int          getH	          ()         const { return h_; }
                      int          getH	          (Node* n)  const { return (std::abs(n->position_.x - position_.x) + std::abs(n->position_.y - position_.y))*10; }
             };

             static Node* getNode (int tiles[], sf::Vector2i position) {
                 bool walkable = true;
                 if (  tiles[position.x + 77*position.y] == 0
                    || tiles[position.x + 77*position.y] == 1
                     ) walkable = false;
                 return new Node(position, walkable);
             }
    
    public:  static std::vector<sf::Vector2i> aStar     (sf::Vector2i from, sf::Vector2i to, int tiles[]);
    };

}

#endif // PATHFINDER_HPP
