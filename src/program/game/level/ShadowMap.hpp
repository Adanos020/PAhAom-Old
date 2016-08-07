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
    private: bool            discovered_[77*43];
             char            cellIDs_ [3*77*43];

             sf::Vector2u    size_;
             sf::VertexArray shadowSprite_;
             sf::Texture     shadowTexture_;
             sf::Image       shadowImage_;

             void fillCell             (unsigned x, unsigned y, char id);
             bool isFilled             (unsigned x, unsigned y, char id) const;

     virtual void draw                 (sf::RenderTarget&, sf::RenderStates) const;

    public:  void setLit               (unsigned x, unsigned y);
             void darken               ();

             void update               ();

             std::ifstream& operator<< (std::ifstream&);
             std::ofstream& operator>> (std::ofstream&);

             ShadowMap(sf::Vector2u size);
    };

}

#endif // SHADOWMAP_HPP
