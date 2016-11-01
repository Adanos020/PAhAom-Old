/**
 * @file src/program/gui/Checkbox.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Checkbox.hpp"

#include "../Resources.hpp"

namespace rr
{

    Checkbox::Checkbox(sf::Vector2f pos, sf::String txt, int chsize, sf::Color c) :
      m_image(Image(pos, Resources::texture.gui, 14, 1)),
      m_text (Text (sf::Vector2f(0, 0), txt, Resources::font.Unifont, chsize))
    {
        m_body.setSize            (sf::Vector2f(35, 35));
        m_body.setPosition        (pos);
        m_body.setFillColor       (c);
        m_body.setOutlineColor    (sf::Color(c.r+20, c.g+20, c.b+20));
        m_body.setOutlineThickness(5);

        m_text.setPosition(sf::Vector2f(pos.x+45, pos.y+m_body.getSize().y/2-m_text.getSize().y));

        m_image.setParentComponent(this);
        m_text .setParentComponent(this);
    }

    void
    Checkbox::check(bool b)
    {
        m_checked = b;
    }

    void
    Checkbox::setPosition(sf::Vector2f pos)
    {
        m_body .setPosition(pos);
        m_text .setPosition(sf::Vector2f(pos.x+45, pos.y+m_body.getSize().y/2-m_text.getSize().y));
        m_image.setPosition(pos);
    }

    void
    Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_body , states);
        if (m_checked)
            target.draw(m_image, states);
        target.draw(m_text , states);
    }

    bool
    Checkbox::containsMouseCursor(sf::RenderWindow& rw)
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
    Checkbox::isPressed(sf::RenderWindow& rw, sf::Event& e)
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

}
