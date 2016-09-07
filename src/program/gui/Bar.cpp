/**
 * @file src/program/gui/Bar.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Bar.hpp"

namespace rr
{

    Bar::Bar(Plain plain, int max_length, sf::Color c, sf::Vector2f pos)
    {
        if (plain == HORIZONTAL)
        {
            m_border.setSize(sf::Vector2f(max_length, 5));
            m_bar   .setSize(sf::Vector2f(max_length, 5));
        }
        else if (plain == VERTICAL)
        {
            m_border.setSize(sf::Vector2f(5, max_length));
            m_bar   .setSize(sf::Vector2f(5, max_length));
        }

        m_border.setFillColor       (sf::Color::Transparent);
        m_border.setOutlineColor    (sf::Color(128, 128, 128));
        m_border.setOutlineThickness(5);
        m_border.setPosition        (pos);

        m_bar.setFillColor(c);
        m_bar.setPosition (pos);
    }

    void
    Bar::setPosition(sf::Vector2f pos)
    {
        m_border.setPosition(pos);
        m_bar   .setPosition(pos);
    }

    void
    Bar::setSize(sf::Vector2f size)
    {
        //m_bar.setSize(sf::Vector2f(m_border.getSize().x/size.x * m_bar.getSize().x));
        m_border.setSize(size);
    }

    void
    Bar::setValue(sf::Vector2f scale)
    {
        if      (m_bar.getSize().x == 5) m_bar.setScale(1, scale.y);
        else if (m_bar.getSize().y == 5) m_bar.setScale(scale.x, 1);
    }

    void
    Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_bar   , states);
        target.draw(m_border, states);
    }

}
