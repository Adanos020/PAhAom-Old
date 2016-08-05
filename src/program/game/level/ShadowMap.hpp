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
    private: sf::Vector2i size_;
     mutable sf::Texture  shadowTexture_;
             bool         discovered_[77*43];
             sf::Uint8    shadows_ [4*77*43];

             void           setColor   (int x, int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a);
             sf::Color      getColor   (int x, int y) const;

             void           fillCell   (int x, int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a);
             bool           isFilled   (int x, int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) const;

             virtual void   draw       (sf::RenderTarget&, sf::RenderStates) const;

    public:  void           setLit     (int x, int y);
             void           darken     ();

             std::ifstream& operator<< (std::ifstream&);
             std::ofstream& operator>> (std::ofstream&);

             ShadowMap(sf::Vector2i size);
    };

}

#endif // SHADOWMAP_HPP
