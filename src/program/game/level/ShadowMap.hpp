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
    private: sf::Image    shadows_;
             sf::Vector2i size_;
             bool         discovered_[77*43];

             void           fillCell   (int x, int y, sf::Color);

             virtual void   draw       (sf::RenderTarget&, sf::RenderStates) const;

    public:  void           setLit     (int x, int y);
             void           darken     ();

             std::ifstream& operator<< (std::ifstream&);
             std::ofstream& operator>> (std::ofstream&);

             ShadowMap(sf::Vector2i size);
    };

}

#endif // SHADOWMAP_HPP
