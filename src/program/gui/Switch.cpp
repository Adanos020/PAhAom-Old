/**
 * @file src/program/gui/Switch.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Switch.hpp"

#include "../../Program.hpp"

namespace rr
{

    Switch::Switch(sf::Vector2f size, sf::Vector2f pos) :
      m_left (Button(pos, "<", 30)),
      m_right(Button(sf::Vector2f(m_body.getPosition().x + m_body.getSize().x+24, pos.y), ">", 30)),
      m_text (Text  (sf::Vector2f(0, 0), L"QYTA CLOHJÉR", Resources::font.Unifont, size.y))
    {
        m_body .setSize            (size);
        m_body .setPosition        (sf::Vector2f(pos.x+44, pos.y+5));
        m_body .setFillColor       (sf::Color(128, 128, 128, 128));
        m_body .setOutlineColor    (sf::Color(108, 108, 108));
        m_body .setOutlineThickness(5);

        m_left .setParentComponent (this);
        m_right.setParentComponent (this);
        m_text .setParentComponent (this);

        setPosition(pos);

        m_counter = 0;
    }

    void
    Switch::setPosition(sf::Vector2f pos)
    {
        m_left .setPosition(pos);
        m_body .setPosition(sf::Vector2f(pos.x+44, pos.y+5));
        m_text .setPosition(sf::Vector2f(m_body.getPosition().x + m_body.getSize().x/2 - m_text.getSize().x/2, m_body.getPosition().y-4));
        m_right.setPosition(sf::Vector2f(pos.x+m_body.getSize().x + m_body.getSize().y+21, pos.y));
    }

    void
    Switch::setSize(sf::Vector2f s)
    {
        m_body .setSize(s);
        m_right.setPosition(sf::Vector2f(s.x+s.x+s.y+11, s.y));
    }

    void
    Switch::buttonEvents(sf::RenderWindow& rw, sf::Event& e)
    {
        if (m_left.isPressed(rw, e))
        {
            if (m_counter > 0)
                m_counter--;
            else
                m_counter = m_options.size()-1;
            
            m_text.setString  (m_options[m_counter]);
            m_text.setPosition(sf::Vector2f(m_body.getPosition().x + m_body.getSize().x/2 - m_text.getSize().x/2, m_body.getPosition().y-4));
        }
        else if (m_right.isPressed(rw, e))
        {
            if (m_counter<m_options.size()-1)
                m_counter++;
            else
                m_counter = 0;
            
            m_text.setString  (m_options[m_counter]);
            m_text.setPosition(sf::Vector2f(m_body.getPosition().x + m_body.getSize().x/2 - m_text.getSize().x/2, m_body.getPosition().y-4));
        }
    }

    void
    Switch::addOption(sf::String opt)
    {
        m_options.push_back(opt);
        if (m_options.size() == 1)
        {
            m_text.setString  (m_options[m_counter]);
            m_text.setPosition(sf::Vector2f(m_body.getPosition().x + m_body.getSize().x/2 - m_text.getSize().x/2, m_body.getPosition().y-4));
        }
    }

    void
    Switch::setCurrentOption(sf::String o)
    {
        int i = 0;
        for (auto x : m_options)
        {
            if (x == o)
                break;
            ++i;
        }
        m_counter = i;
        m_text.setString  (m_options[m_counter]);
        m_text.setPosition(sf::Vector2f(m_body.getPosition().x + m_body.getSize().x/2 - m_text.getSize().x/2, m_body.getPosition().y-4));
    }

    void
    Switch::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_body , states);
        target.draw(m_left , states);
        target.draw(m_right, states);
        target.draw(m_text , states);
    }

}
