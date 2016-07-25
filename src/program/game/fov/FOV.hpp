/**
 * @file src/program/game/fov/FOV.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FOV_HPP
#define FOV_HPP

#include "../entity/Shadow.hpp"

namespace rr {

    class FOV final {
    private: struct Slope {
             public: unsigned x_, y_;
                     Slope(unsigned y, unsigned x) { y_ = y; x_ = x; }

                     bool operator> (Slope slope) { return y_*slope.x_ >  x_*slope.y_; }
                     bool operator< (Slope slope) { return y_*slope.x_ <  x_*slope.y_; }
                     bool operator>=(Slope slope) { return y_*slope.x_ >= x_*slope.y_; }
                     bool operator<=(Slope slope) { return y_*slope.x_ <= x_*slope.y_; }
             };
         
             static void compute    (Shadow[]   , int tiles[], unsigned octant    , sf::Vector2u origin, int range          , unsigned x, Slope top, Slope bottom);
             static bool blocksLight(int tiles[], unsigned x , unsigned y         , unsigned octant    , sf::Vector2u origin);
             static void setVisible (Shadow[]   , unsigned x , unsigned y         , unsigned octant    , sf::Vector2u origin);
             static int  getDistance(int x      , int y);
             static void smoothShade(Shadow[]);
    
    public:  static void compute    (Shadow[]   , int tiles[], sf::Vector2u origin, int range);
    };

}

#endif // FOV_HPP
