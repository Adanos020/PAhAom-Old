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
    private: bool               discovered_[77*43];
             unsigned char      cellIDs_ [9*77*43];

             sf::Vector2u       size_;
             sf::RectangleShape shadowSprite_;
             sf::Texture        shadowTexture_;
             sf::Image          shadowImage_;

             bool isFilled            (unsigned x, unsigned y, unsigned char id) const;

     virtual void draw                (sf::RenderTarget&, sf::RenderStates)      const;

    public:  void setLit              (unsigned x, unsigned y);
             void darken              ();

             void update              ();

             std::ifstream& operator<<(std::ifstream&);
             std::ofstream& operator>>(std::ofstream&);

             ShadowMap(sf::Vector2u size);
    };

}

#endif // SHADOWMAP_HPP
