/**
 * @file src/program/game/fov/FOV.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FOV_HPP
#define FOV_HPP

#include "../level/ShadowMap.hpp"

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

             ////////////////////////////////////////////////////////////////////////
             /// \brief Calculates the possible field of vision from a given point on the
             /// tile map.
             ////////////////////////////////////////////////////////////////////////
      static void compute(ShadowMap* shadows, int tiles[], unsigned octant, sf::Vector2i origin, int range, unsigned x, Slope top, Slope bottom);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if a block in a given position blocks light.
             ////////////////////////////////////////////////////////////////////////
      static bool blocksLight(int tiles[], int x, int y, unsigned octant, sf::Vector2i origin);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the selected tile visible.
             ////////////////////////////////////////////////////////////////////////
      static void setVisible(ShadowMap* shadows, int x, int y, unsigned octant, sf::Vector2i origin);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Calculates the actual distance between point (0, 0) and point (x, y).
             ////////////////////////////////////////////////////////////////////////
      static int getDistance(int x, int y);

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Calculates the possible field of vision from a given point on the
             /// tile map.
             ////////////////////////////////////////////////////////////////////////
      static void compute(ShadowMap* shadows, int tiles[], sf::Vector2i origin, int range);
    };

}

#endif // FOV_HPP
