/**
 * @file src/program/gui/Image.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Image.hpp"

namespace rr
{

    Image::Image(sf::Vector2f pos, sf::Texture& texture, int iconSize, unsigned index) :
      m_icon(iconSize)
    {
        if (iconSize != -1)
        {
            unsigned tu = index%(texture.getSize().x/m_icon);
            unsigned tv = index/(texture.getSize().y/m_icon);
            m_body.setTextureRect(sf::IntRect(tu*m_icon, tv*m_icon, m_icon, m_icon));
        }

        m_body.setPosition(pos);
        m_body.setTexture (texture);
        m_body.scale      (sf::Vector2f(5, 5));
    }

    void
    Image::setIconIndex(unsigned index)
    {
        unsigned tu = index%(m_body.getTexture()->getSize().x/m_icon);
        unsigned tv = index/(m_body.getTexture()->getSize().y/m_icon);

        m_body.setTextureRect(sf::IntRect(tu*m_icon, tv*m_icon, m_icon, m_icon));
    }

    void
    Image::setTexture(sf::Texture& texture)
    {
        m_body.setTexture(texture);
    }

    void
    Image::scale(sf::Vector2f v)
    {
        m_body.scale(v);
    }

    void
    Image::paint(sf::Color c)
    {
        m_body.setColor(c);
    }

    void
    Image::setPosition(sf::Vector2f pos)
    {
        m_body.setPosition(pos);
    }

    void
    Image::setSize(sf::Vector2f size)
    {
        m_body.setScale(sf::Vector2f(size.x/m_body.getGlobalBounds().width, size.y/m_body.getGlobalBounds().height));
    }

    void
    Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_body, states);
    }
}
