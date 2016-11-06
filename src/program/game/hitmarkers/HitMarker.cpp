/**
 * @file src/program/game/hitmarkers/HitMarker.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../HitMarkerManager.hpp"

#include "../../Resources.hpp"

namespace rr
{

// PRIVATE

    void HitMarker::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_text, states);
    }

// PUBLIC

    HitMarker::HitMarker(sf::String text, sf::Color color, sf::Vector2f pos) :
      m_timeElapsed(sf::Time::Zero),
      m_lifeTime   (sf::seconds(3.f))
    {
        m_text.setString(text);
        m_text.setFillColor(color);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(3);
        m_text.setFont(Resources::font.FinalFantasy);
        m_text.setCharacterSize(35);

        m_text.setPosition(pos - sf::Vector2f(m_text.getGlobalBounds().width / 2, 40));
    }

    void
    HitMarker::update(sf::Time& delta)
    {
        m_timeElapsed += delta;

        if (m_timeElapsed <= m_lifeTime)
        {
            m_text.move(sf::Vector2f(0, -50 * delta.asSeconds()));

            sf::Color newColor = m_text.getFillColor();
            newColor.a -= 6 * delta.asSeconds();
            m_text.setFillColor(newColor);
            
            newColor = m_text.getOutlineColor();
            newColor.a -= 6 * delta.asSeconds();
            m_text.setOutlineColor(newColor);
        }
    }

}
