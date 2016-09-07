/**
 * @file src/program/gui/Menu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Menu.hpp"

namespace rr
{

    Menu::Menu(sf::Vector2f position)
    {
        m_position = position;
    }

    Menu::~Menu()
    {
        m_options.clear();
    }

    void
    Menu::addOption(sf::String option)
    {
        m_options.push_back(Button(m_position + sf::Vector2f(0, m_options.size()*40), option, 25));
    }

    void
    Menu::setOption(unsigned index, sf::String option)
    {
        m_options[index].getText().setString(option);
    }

    void
    Menu::removeOption(unsigned index)
    {
        m_options.erase(m_options.begin()+index);
        for (int i = 0; i < (int) m_options.size(); ++i)
        {
            m_options[i].setPosition(m_position + sf::Vector2f(0, i*40));
        }
    }

    sf::String
    Menu::getChosenOption(sf::RenderWindow& rw, sf::Event& event)
    {
        for (unsigned i = 0; i < m_options.size(); ++i) {
            if (m_options[i].isPressed(rw, event))
                return m_options[i].getText().getString();
        }
        return "";
    }

    void
    Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto button : m_options) {
            target.draw(button, states);
        }
    }

    void
    Menu::setPosition(sf::Vector2f position)
    {
        m_position = position;
        for (int i = 0; i < (int) m_options.size(); ++i)
        {
            m_options[i].setPosition(position + sf::Vector2f(0, i*40));
        }
    }

}
