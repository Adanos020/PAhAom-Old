/**
 * @file src/program/game/shadowmap/ShadowMap.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef SHADOWMAP_HPP
#define SHADOWMAP_HPP

#include <SFML/Graphics.hpp>

namespace rr {
    class ShadowMap : public sf::Drawable {
    private: sf::VertexArray shadows_;
             sf::Vector2i    size_;
             bool            discovered_[77*43];
             bool            flipped_   [77*43];

             virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    
    public:  ShadowMap(sf::Vector2i size);

             void           setLit      (sf::Vector2i);
             void           darken      ();
             bool           isDiscovered(sf::Vector2i pos) const { return discovered_[pos.x + 77*pos.y]; }

             std::ifstream& operator<<  (std::ifstream&);
             std::ofstream& operator>>  (std::ofstream&);
    };
}

#endif // SHADOWMAP_HPP
