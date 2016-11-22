/**
 * @file src/program/game/messages/Message.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../MessageManager.hpp"

#include "../../Resources.hpp"

namespace rr
{

    Message::Message(sf::String text, sf::Color color, sf::Text::Style textStyle) :
      m_message    (Text(text, Resources::font.Unifont, 16, color, textStyle)),
      m_timeElapsed(sf::Time::Zero),
      m_lifeTime   (sf::seconds(5))
    {
        m_message.setOutlineColor(sf::Color::Black);
        m_message.setOutlineThickness(1);
        m_message.wrap(400);
    }

    void
    Message::setPosition(sf::Vector2f position)
    {
        m_message.setPosition(position);
    }

    void
    Message::update(sf::Time& timeStep)
    {
        m_timeElapsed += timeStep;

        if (m_timeElapsed >= m_lifeTime)
        {
            sf::Color newColor = m_message.getFillColor();
            newColor.a -= 5;
            m_message.setFillColor(newColor);
        }
    }

    void
    Message::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_message, states);
    }

}
