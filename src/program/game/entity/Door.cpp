/**
 * @file src/program/game/entity/Door.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "../../Resources.hpp"

#include "../../funcs/files.hpp"

#include "Door.hpp"

namespace rr
{

    Door::Door(bool lock) :
      m_locked      (lock),
      m_open        (false),
      m_withWindow(rand()%2)
    {
        initialize();
    }

    Door::Door(Door const& copy) :
      m_body      (copy.m_body),
      m_locked    (copy.m_locked),
      m_open      (copy.m_open),
      m_withWindow(copy.m_withWindow) {}

    void
    Door::initialize()
    {
        m_body.setTexture(Resources::texture.objects);
        m_body.setScale(sf::Vector2f(5, 5));
        m_body.setTextureRect(sf::IntRect(sf::Vector2i(rand()%5*16*((!m_withWindow)+1), 0), sf::Vector2i(16, 16)));
    }

    void
    Door::setOpen(bool b)
    {
        m_open = b;
        if (m_open)
        {
            m_body.setTextureRect(sf::IntRect(sf::Vector2i(m_body.getTextureRect().left%80, 16), sf::Vector2i(16, 16)));
            m_locked = false;
        }
        else
            m_body.setTextureRect(sf::IntRect(sf::Vector2i(m_body.getTextureRect().left%80 + 80*(!m_withWindow), 0), sf::Vector2i(16, 16)));
    }

    void
    Door::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = &Resources::texture.objects;
        target.draw(m_body, states);
    }

    std::ifstream&
    Door::operator<<(std::ifstream& file) {
        sf::Vector2i position;

        try
        {
            readFile <int > (file, position.x);
            readFile <int > (file, position.y);
            readFile <bool> (file, m_locked);
            readFile <bool> (file, m_open);
            readFile <bool> (file, m_withWindow);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Door::operator>>(std::ofstream& file)
    {
        file << 41                              << ' '
             << (int) m_body.getPosition().x/80 << ' '
             << (int) m_body.getPosition().y/80 << ' '
             << m_locked                        << ' '
             << m_open                          << ' '
             << m_withWindow;

        return file;
    }
}
