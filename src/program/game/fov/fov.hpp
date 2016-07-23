/**
 * @file src/program/game/fov/fov.hpp
 * @author Adam 'Adanos' G�sior
 * Used library: SFML 2.3.2
 */

#ifndef fov_hpp
#define fov_hpp

#include "../entities/mask/mask.hpp"

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
         
             static void compute    (Mask[]     , int tiles[], unsigned octant    , sf::Vector2u origin, int range          , unsigned x, Slope top, Slope bottom);
             static bool blocksLight(int tiles[], unsigned x , unsigned y         , unsigned octant    , sf::Vector2u origin);
             static void setVisible (Mask[]     , unsigned x , unsigned y         , unsigned octant    , sf::Vector2u origin);
             static int  getDistance(int x      , int y);
             static void smoothShade(Mask[]);
    
    public:  static void compute    (Mask[]     , int tiles[], sf::Vector2u origin, int range);
    };

}

#endif // fov_hpp
