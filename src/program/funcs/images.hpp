/**
 * @file src/program/funcs/images.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FUNCS_IMAGES_HPP
#define FUNCS_IMAGES_HPP

#include <SFML/Graphics.hpp>

namespace rr
{

    ////////////////////////////////////////////////////////////////////////
    /// \brief Sets the icons for each layer of a custom sprite's texture.
    ///
    /// \param body the vertex array of a sprite
    /// \param layers the number of layers we want to set
    /// \param icons the array of icon indices in an order from the bottom
    /// to the top
    ///
    /// It works in such a way that it just gives the indices relevant
    /// texture coordinates.
    ////////////////////////////////////////////////////////////////////////
    inline void
    setIcon(sf::VertexArray& body, int layers, int icons[])
    {
        body.resize(4*layers);
        body.setPrimitiveType(sf::Quads);

        for (int i = 0; i < layers; i++)
        {
            int tu = icons[i]%16;
            int tv = icons[i]/16;

            body[4*i+0].texCoords =  sf::Vector2f(  tu  *16+0.0001f,   tv  *16+0.0001f);
            body[4*i+1].texCoords =  sf::Vector2f((tu+1)*16-0.0001f,   tv  *16+0.0001f);
            body[4*i+2].texCoords =  sf::Vector2f((tu+1)*16-0.0001f, (tv+1)*16-0.0001f);
            body[4*i+3].texCoords =  sf::Vector2f(  tu  *16+0.0001f, (tv+1)*16-0.0001f);
        }
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Sets the icons of a custom sprite's texture.
    ///
    /// \param body the vertex array of a sprite
    /// \param icon the icon index
    ///
    /// It works in such a way that it just gives the indices relevant
    /// texture coordinates.
    ////////////////////////////////////////////////////////////////////////
    inline void
    setIcon(sf::VertexArray& body, int icon)
    {
        body.resize(4);
        body.setPrimitiveType(sf::Quads);

        int hor = icon%16;
        int ver = icon/16;

        body[0].texCoords =  sf::Vector2f(  hor  *16+0.0001f,   ver  *16+0.0001f);
        body[1].texCoords =  sf::Vector2f((hor+1)*16-0.0001f,   ver  *16+0.0001f);
        body[2].texCoords =  sf::Vector2f((hor+1)*16-0.0001f, (ver+1)*16-0.0001f);
        body[3].texCoords =  sf::Vector2f(  hor  *16+0.0001f, (ver+1)*16-0.0001f);
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Sets the color of a given layer of the custom sprite's
    /// texture.
    ////////////////////////////////////////////////////////////////////////
    inline void
    setColor(sf::VertexArray& body, int layer, sf::Color color)
    {
        for (int i = 0; i < 4; i++)
        {
            body[4*layer+i].color = color;
        }
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Sets the color of all layers of the custom sprite's texture.
    ////////////////////////////////////////////////////////////////////////
    inline void
    setColor(sf::VertexArray& body, sf::Color color)
    {
        for (unsigned i = 0; i < body.getVertexCount(); i++)
        {
            body[i].color = color;
        }
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Makes a gradient from the color array on a given layer. 
    ////////////////////////////////////////////////////////////////////////
    inline void
    setGradient(sf::VertexArray& body, int layer, sf::Color colors[])
    {
        body[4*layer+0].color = colors[0];
        body[4*layer+1].color = colors[1];
        body[4*layer+2].color = colors[2];
        body[4*layer+3].color = colors[3];
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Sets the custom sprite's position.
    ////////////////////////////////////////////////////////////////////////
    inline void
    setPosition(sf::VertexArray& body, sf::Vector2f pos)
    {
        body[1].position = pos+(body[1].position-body[0].position);
        body[2].position = pos+(body[2].position-body[0].position);
        body[3].position = pos+(body[3].position-body[0].position);
        body[0].position = pos;

        if (body.getVertexCount() > 4)
        {
            for (unsigned i = 4; i < body.getVertexCount(); i++)
            {
                body[i].position = body[i%4].position;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Sets the custom sprite's size.
    ////////////////////////////////////////////////////////////////////////
    inline void
    setSize(sf::VertexArray& body, sf::Vector2f siz)
    {
        body[1].position = body[0].position+sf::Vector2f(siz.x,     0);
        body[2].position = body[0].position+sf::Vector2f(siz.x, siz.y);
        body[3].position = body[0].position+sf::Vector2f(0    , siz.y);
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Flips the custom sprite vertically.
    ////////////////////////////////////////////////////////////////////////
    inline void
    flipVertically(sf::VertexArray& body)
    {
        sf::Vector2f position_0 = body[0].position,
                     position_1 = body[1].position,
                     position_2 = body[2].position,
                     position_3 = body[3].position;

        body[0].position = position_3;
        body[1].position = position_2;
        body[2].position = position_1;
        body[3].position = position_0;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Flips the custom sprite horizontally.
    ////////////////////////////////////////////////////////////////////////
    inline void
    flipHorizontally(sf::VertexArray& body)
    {
        sf::Vector2f position_0 = body[0].position,
                     position_1 = body[1].position,
                     position_2 = body[2].position,
                     position_3 = body[3].position;

        body[0].position = position_1;
        body[3].position = position_2;
        body[1].position = position_0;
        body[2].position = position_3;
    }

}

#endif // FUNCS_IMAGES_HPP
