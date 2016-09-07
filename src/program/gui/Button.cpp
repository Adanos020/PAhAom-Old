/**
 * @file src/program/gui/Button.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Button.hpp"

#include "../Resources.hpp"

namespace rr
{

    Button::Button(sf::Vector2f position, sf::String str, unsigned chsize, sf::Color c) :
      m_image(Image(position, Resources::texture.gui, 14, 0)),
      m_text (Text (sf::Vector2f(0, 0), str, Resources::font.Unifont, chsize, c)),
      m_held (false)
    {
        m_text.setParentComponent(this);

        m_image.setParentComponent(this);

        m_body.setPosition(position);
        m_body.setSize(sf::Vector2f(m_text.getSize().x+25, chsize*1.3425));
        m_body.setFillColor(sf::Color(0, 0, 0));
        m_body.setOutlineColor(sf::Color::Black);
        m_body.setOutlineThickness((float) chsize/20.f);

        m_text.setPosition(sf::Vector2f(position.x + m_body.getSize().x/2 - m_text.getSize().x/2 - chsize/20,
                                        position.y - 0.5));
    }

    void
    Button::setText(sf::String s)
    {
        m_text.setString(s);
        m_body.setSize(sf::Vector2f(m_text.getSize().x+25, m_text.getCharacterSize()*1.3425));
        m_body.setFillColor(sf::Color(0, 0, 0));

        m_text.setPosition(sf::Vector2f(m_body.getPosition().x + m_body.getSize().x/2 - m_text.getSize().x/2 - m_text.getCharacterSize()/20,
                                         m_body.getPosition().y-0.5));
    }

    bool
    Button::containsMouseCursor(sf::RenderWindow& rw)
    {
        if (m_body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw)))
        {
            m_body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        m_body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool
    Button::isPressed(sf::RenderWindow& rw, sf::Event& e)
    {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
        {
            m_held = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            m_held = false;
        return false;
    }

    void
    Button::setPosition(sf::Vector2f position)
    {
        m_body .setPosition(position);
        m_text .setPosition(sf::Vector2f(position.x+m_body.getSize().x/2-m_text.getSize().x/2-m_text.getCharacterSize()/20, position.y-0.5));
        m_image.setPosition(position);
    }

    void
    Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_body , states);
        target.draw(m_text , states);
        target.draw(m_image, states);
    }

}
