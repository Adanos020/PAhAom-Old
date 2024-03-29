/**
 * @file src/program/game/FOV.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include "ShadowMap.hpp"

#include "Entity.hpp"
#include "entity/NPC.hpp"

namespace rr
{

    class FOV final
    {
    private: struct Slope
             {
             public: unsigned x_, y_;
                     Slope(unsigned y, unsigned x) { y_ = y; x_ = x; }

                     bool operator> (Slope slope) { return y_*slope.x_ >  x_*slope.y_; }
                     bool operator< (Slope slope) { return y_*slope.x_ <  x_*slope.y_; }
                     bool operator>=(Slope slope) { return y_*slope.x_ >= x_*slope.y_; }
                     bool operator<=(Slope slope) { return y_*slope.x_ <= x_*slope.y_; }
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Calculates the possible field of vision from a given point on
             /// the tile map.
             ////////////////////////////////////////////////////////////////////////
      static void compute(ShadowMap&, Level&, unsigned octant, sf::Vector2i origin, int range, unsigned x, Slope top, Slope bottom);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if an entity is in the NPC's field of vision.
             ///
             /// \param npc the npc whose field of vision is calculated
             /// \param entity the entity which may be detected by the NPC
             ////////////////////////////////////////////////////////////////////////
      static bool seesEntity(Level&, unsigned octant, sf::Vector2i origin, sf::Vector2i dest, int range, unsigned x, Slope top, Slope bottom);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if a block in a given position blocks light.
             ////////////////////////////////////////////////////////////////////////
      static bool blocksLight(Level&, int x, int y, unsigned octant, sf::Vector2i origin);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the selected tile visible.
             ////////////////////////////////////////////////////////////////////////
      static void setVisible(ShadowMap&, int x, int y, unsigned octant, sf::Vector2i origin);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the visible tile's position.
             ////////////////////////////////////////////////////////////////////////
      static sf::Vector2i getVisible(int x, int y, unsigned octant, sf::Vector2i origin);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Calculates the actual distance between point (0, 0) and point
             /// (x, y).
             ////////////////////////////////////////////////////////////////////////
      static int getDistance(int x, int y);

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Calculates the possible field of vision from a given point on
             /// the tile map.
             ////////////////////////////////////////////////////////////////////////
      static void compute(ShadowMap&, Level&, sf::Vector2i origin, int range);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if an entity is in the NPC's field of vision.
             ////////////////////////////////////////////////////////////////////////
      static bool seesEntity(Level&, Entity* e1, Entity* e2);
    };

}
