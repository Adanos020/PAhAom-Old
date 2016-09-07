/**
 * @file src/program/game/entity/Stairs.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "../../Resources.hpp"

#include "../../funcs/files.hpp"

#include "Stairs.hpp"

namespace rr
{

    Stairs::Stairs(bool upwards) :
      m_upwards(upwards)
    {
        initialize();
    }

    Stairs::Stairs(Stairs const& copy) :
      m_body   (copy.m_body   ),
      m_upwards(copy.m_upwards) {}

    void
    Stairs::initialize()
    {
        m_body.setTexture    (Resources::texture.objects);
        m_body.setScale      (sf::Vector2f(5, 5));
        m_body.setTextureRect(sf::IntRect(m_upwards ? 16 : 0, 64, 16, 16));
    }

    void
    Stairs::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = &Resources::texture.objects;
        target.draw(m_body, states);
    }

    std::ifstream&
    Stairs::operator<<(std::ifstream& file)
    {
        sf::Vector2i position;

        try
        {
            readFile < int> (file, position.x);
            readFile < int> (file, position.y);
            readFile <bool> (file, m_upwards);
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
    Stairs::operator>>(std::ofstream& file)
    {
        file << 42                             << ' '
             << (int) m_body.getPosition().x/80 << ' '
             << (int) m_body.getPosition().y/80 << ' '
             << m_upwards;

        return file;
    }

}
