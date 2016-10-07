/**
 * @file src/program/gui/Separator.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Separator.hpp"

namespace rr
{

    // PRIVATE
    
    void
    Separator::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_vertices, states);
    }

    // PUBLIC

    Separator::Separator(Separator::Plain plain, float length)
    {
        m_length = length;

        m_vertices.resize(2);
        m_vertices.setPrimitiveType(sf::Lines);

        m_vertices[0].position = sf::Vector2f(0, 0);

        if (plain == HORIZONTAL)
            m_vertices[1].position = sf::Vector2f(length, 0);
        else
            m_vertices[1].position = sf::Vector2f(0, length);
    }

    void
    Separator::setLength(float length)
    {
        m_length = length;

        if (m_plain == HORIZONTAL)
            m_vertices[1].position = sf::Vector2f(length, 0);
        else
            m_vertices[1].position = sf::Vector2f(0, length);
    }

    float
    Separator::getLength() const
    {
        return m_length;
    }

    void
    Separator::setColor(sf::Color color)
    {
        m_vertices[0].color = color;
        m_vertices[1].color = color;
    }

    sf::Color
    Separator::getColor() const
    {
        return m_vertices[0].color;
    }

    void
    Separator::setPosition(sf::Vector2f pos)
    {
        auto distance = m_vertices[1].position - m_vertices[0].position;
        m_vertices[0].position = pos;
        m_vertices[1].position = pos + distance;
    }

    sf::Vector2f
    Separator::getPosition() const
    {
        return m_vertices[0].position;
    }

    sf::Vector2f
    Separator::getSize() const
    {
        return m_vertices[1].position - m_vertices[0].position;
    }

}
