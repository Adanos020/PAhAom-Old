/**
 * @file src/program/game/fov/fov.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef fov_hpp
#define fov_hpp

#include "../entities/mask/mask.hpp"

namespace rr {

    class FOV final {
    private:
        std::vector<std::vector<Mask*>>* masks_;
        std::vector<std::vector<int>>*   tiles_;

        struct Slope {
        public:
            unsigned x_, y_;
            Slope(unsigned y, unsigned x) { y_ = y; x_ = x; }

            bool operator> (Slope slope) { return y_*slope.x_ >  x_*slope.y_; }
            bool operator< (Slope slope) { return y_*slope.x_ <  x_*slope.y_; }
            bool operator>=(Slope slope) { return y_*slope.x_ >= x_*slope.y_; }
            bool operator<=(Slope slope) { return y_*slope.x_ <= x_*slope.y_; }
        };

        void compute    (unsigned octant, sf::Vector2u origin, int range, unsigned x, Slope top, Slope bottom);
        bool blocksLight(unsigned x, unsigned y, unsigned octant, sf::Vector2u origin);
        void setVisible (unsigned x, unsigned y, unsigned octant, sf::Vector2u origin);
        int  getDistance(int x, int y);
    public:
        FOV(std::vector<std::vector<Mask*>>* masks, std::vector<std::vector<int>>* tiles);

        void compute(sf::Vector2u origin, int range);
    };

}

#endif // fov_hpp
