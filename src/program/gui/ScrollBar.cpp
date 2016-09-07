/**
 * @file src/program/gui/ScrollBar.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "ScrollBar.hpp"

#include "../Resources.hpp"

namespace rr
{

    ScrollBar::ScrollBar(Plain p, sf::Vector2f position, float length, sf::Vector2f min_max) :
      m_valueLimit(min_max),
      m_indicator (Button(position+sf::Vector2f(10, 5), "|", 30)),
      m_bLeft     (Button(position, "<", 30)),
      m_bRight    (Button(position+sf::Vector2f(length, 0), ">", 30)),
      m_label     (Text(sf::Vector2f(0, 0), "", Resources::font.Unifont)),
      m_value     (m_valueLimit.x),
      m_plain     (p)
    {
        if (p == VERTICAL)
        {
            m_bLeft     = Button(position, L"∧", 30);
            m_bRight    = Button(position+sf::Vector2f(0, length+20), L"∨", 30);
            m_indicator = Button(position+sf::Vector2f(0, 10), "_", 30);
            m_label     = Text  (sf::Vector2f(0, 0), "", Resources::font.Unifont);

            m_border.setPosition(m_bLeft.getPosition() + sf::Vector2f(m_bLeft.getSize().x+10, 5));
            m_border.setOutlineThickness(1);
            m_border.setOutlineColor(sf::Color::Black);
            m_border.setFillColor(sf::Color(128, 128, 128, 128));
            m_border.setSize(sf::Vector2f(33, length));

            m_label .setPosition(m_border.getPosition() + sf::Vector2f(-5, m_border.getSize().y/2 - m_label.getSize().y/2));
        }
        else
        {
            m_border.setPosition(m_bLeft.getPosition() + sf::Vector2f(m_bLeft.getSize().x+5, 5));
            m_border.setOutlineThickness(1);
            m_border.setOutlineColor(sf::Color::Black);
            m_border.setFillColor(sf::Color(128, 128, 128, 128));
            m_border.setSize(sf::Vector2f(length, 40));

            m_label.setPosition(m_border.getPosition() + sf::Vector2f(m_border.getSize().x/2 - m_label.getSize().x/2, m_border.getSize().y/2 - m_label.getSize().y/2-10));
        }
    }

    void
    ScrollBar::setPosition(sf::Vector2f pos)
    {
        if (m_plain == HORIZONTAL)
        {
            m_bLeft    .setPosition(pos);
            m_border   .setPosition(m_bLeft .getPosition() + sf::Vector2f(m_bLeft.getSize().x, 0));
            m_bRight   .setPosition(m_border.getPosition() + sf::Vector2f(m_border.getSize().x, 0));
            m_indicator.setPosition(m_border.getPosition() + sf::Vector2f(-5, -5));
            m_label    .setPosition(m_border.getPosition()+sf::Vector2f(m_border.getSize().x/2 - m_label.getSize().x/2, m_border.getSize().y/2 - m_label.getSize().y/2-10));
        }
        else if (m_plain == VERTICAL)
        {
            m_bLeft    .setPosition(pos);
            m_border   .setPosition(m_bLeft .getPosition() + sf::Vector2f( 0, m_bLeft.getSize().y));
            m_bRight   .setPosition(m_border.getPosition() + sf::Vector2f( 0, m_border.getSize().y));
            m_indicator.setPosition(m_border.getPosition() + sf::Vector2f(-5, -5));
            m_label    .setPosition(m_bRight.getPosition() + sf::Vector2f(0, m_border.getSize().y/2-m_label.getSize().y/2));
        }
    }

    void
    ScrollBar::setSize(sf::Vector2f siz)
    {
        if (m_plain == HORIZONTAL)
        {
            m_border.setSize    (sf::Vector2f(siz.x, 30));
            m_bRight.setPosition(m_border.getPosition() + sf::Vector2f(m_border.getSize().x+10, 0));
            m_label .setPosition(m_bRight.getPosition() + sf::Vector2f(10, 0));
        }
        else if (m_plain == VERTICAL)
        {
            m_border.setSize    (sf::Vector2f(28, siz.y));
            m_bRight.setPosition(m_border.getPosition() + sf::Vector2f(0, m_border.getSize().y+10));
            m_label .setPosition(m_border.getPosition() + sf::Vector2f(m_border.getSize().x/2 - m_label.getSize().x/2-4, m_border.getSize().y/2 - m_label.getSize().y/2-5));
        }
    }

    void
    ScrollBar::setValue(int val)
    {
        m_value = val;
        if      (m_value < m_valueLimit.x) m_value = m_valueLimit.x;
        else if (m_value > m_valueLimit.y) m_value = m_valueLimit.y;

        m_label.setString  (std::to_string((int) m_value));
        m_label.setPosition(m_border.getPosition() + sf::Vector2f(m_border.getSize().x/2 - m_label.getSize().x/2,
                                                                m_border.getSize().y/2 - m_label.getSize().y/2-10));
    }

    void
    ScrollBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_border   , states);
        target.draw(m_bLeft    , states);
        target.draw(m_bRight   , states);
        target.draw(m_indicator, states);
        target.draw(m_label    , states);
    }

    void
    ScrollBar::buttonEvents(sf::RenderWindow& rw, sf::Event& e)
    {
        auto mousePosition = sf::Mouse::getPosition(rw);

        if ((m_indicator.isPressed(rw, e) || m_indicator.isHeld()))
        {
            if (m_border.getGlobalBounds().contains((sf::Vector2f) mousePosition))
            {
                if (m_plain == HORIZONTAL)
                {
                    m_indicator.setPosition(sf::Vector2f(mousePosition.x-10, m_indicator.getPosition().y));
                    setValue((m_valueLimit.y * (m_indicator.getPosition().x-m_border.getPosition().x-3)) / (m_border.getSize().x-m_indicator.getSize().x+6) + m_valueLimit.x);
                }
                else if (m_plain == VERTICAL)
                {
                    m_indicator.setPosition(sf::Vector2f(m_indicator.getPosition().x, mousePosition.y-10));
                    setValue((m_valueLimit.y * (m_indicator.getPosition().y-m_border.getPosition().y-3)) / (m_border.getSize().y-m_indicator.getSize().y+6) + m_valueLimit.x);
                }
            }
        }
        if (m_bLeft .isPressed(rw, e)) setValue(getValue()-1);
        if (m_bRight.isPressed(rw, e)) setValue(getValue()+1);

        if (m_plain == HORIZONTAL)
            m_indicator.setPosition(m_border.getPosition() + sf::Vector2f((m_border.getSize().x - m_indicator.getSize().x) * (m_value-m_valueLimit.x)/m_valueLimit.y, 0));
        else if (m_plain == VERTICAL)
            m_indicator.setPosition(m_border.getPosition() + sf::Vector2f(0, (m_border.getSize().y - m_indicator.getSize().y) * (m_value-m_valueLimit.x)/m_valueLimit.y));
    }

}
