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
    private: class Point {
             private: Point*       parent_;

                      bool         closed_;
                      bool         opened_;
                      bool         walkable_;

                      sf::Vector2i position_;

                      int          fScore_;
                      int          gScore_;
                      int          hScore_;
             
             public:  Point();
                      Point(sf::Vector2i position, bool walkable);

                      void         calculateScores(Point* goal);

                      void         setParent      (Point* p)       { parent_   = p; }
                      void         setClosed      (bool closed)    { closed_   = closed; }
                      void         setOpened      (bool opened)    { opened_   = opened; }
                      void         setWalkable    (bool walkable)  { walkable_ = walkable; }
                      
                      bool         isClosed       ()         const { return closed_; }
                      bool         isOpened       ()         const { return opened_; }
                      bool         isWalkable     ()         const { return walkable_; }

                      sf::Vector2i getPosition    ()         const { return position_; }
                      sf::Vector2f getFPosition   ()         const { return (sf::Vector2f) position_; }
                      
                      Point*       getParent      ()         const { return parent_; }

                      int          getF	          ()         const { return fScore_; }
                      int          getG	          ()         const { return gScore_; }
                      int          getH	          ()         const { return hScore_; }
                      int          getG	          (Point* p) const { return p->gScore_+((position_.x == p->position_.x || position_.y == p->position_.y) ? 10 : 14); }
                      int          getH	          (Point* p) const { return (std::abs(p->position_.x - position_.x) + std::abs(p->position_.y - position_.y))*10; }
             };

             Point*                    getPoint  (int tiles[], sf::Vector2i position) {
                                                                                          bool walkable = true;
                                                                                          if (  tiles[position.x + 77*position.y] == 0
                                                                                             || tiles[position.x + 77*position.y] == 1
                                                                                              ) walkable = false;
                                                                                          return new PathFinder::Point(position, walkable);
                                                                                      }
    
    public:  std::vector<sf::Vector2i> aStar     (sf::Vector2i from, sf::Vector2i to, int tiles[]);
    };

}

#endif // PATHFINDER_HPP
