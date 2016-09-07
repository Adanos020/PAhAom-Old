/**
 * @file src/program/game/shadowmap/ShadowMap.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef SHADOWMAP_HPP
#define SHADOWMAP_HPP

#include <vector>

#include <SFML/Graphics.hpp>

namespace rr
{

    class ShadowMap : public sf::Drawable
    {
    private: bool                      m_discovered[77*43];
             unsigned char             m_cellIDs [9*77*43];

             sf::Vector2i              m_size;
             sf::VertexArray           m_shadowSprite;
             sf::Texture               m_shadowTexture;
             sf::Image                 m_shadowImage;

             std::vector<sf::Vector2i> m_lastlyLit;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if a 3x3 cell is filled with one color.
             ////////////////////////////////////////////////////////////////////////
             bool isFilled(int x, int y, unsigned char id) const;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the entire shadow map upon the map.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             ShadowMap(sf::Vector2i size);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the chosen cell lit.
             ////////////////////////////////////////////////////////////////////////
             void setLit(int x, int y);
             ////////////////////////////////////////////////////////////////////////
             /// \brief Darkens the recently lit cells.
             ////////////////////////////////////////////////////////////////////////
             void darken();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the texture of whole shadow map.
             ////////////////////////////////////////////////////////////////////////
             void update();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the shadow map from a file.
             ////////////////////////////////////////////////////////////////////////
             std::ifstream& operator<<(std::ifstream&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the shadow map to a file.
             ////////////////////////////////////////////////////////////////////////
             std::ofstream& operator>>(std::ofstream&);
    };

}

#endif // SHADOWMAP_HPP
