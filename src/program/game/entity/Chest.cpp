/**
 * @file src/program/game/entity/Chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Chest.hpp"

#include "../../Resources.hpp"

#include "../../funcs/items.hpp"
#include "../../funcs/files.hpp"

namespace rr
{

    Chest::Chest(Type type) :
      m_item(getRandomItemBalanced()),
      m_type(type)
    {
        initialize();
    }

    Chest::Chest(Chest const& copy) :
      m_body(copy.m_body),
      m_item(copy.m_item),
      m_type(copy.m_type) {}

    Chest::~Chest()
    {
        delete m_item;
    }

    void
    Chest::initialize()
    {
        int tu, tv;
        if (m_type == SPECIAL)
        {
            tu = (rand()%2+18)%(Resources::texture.objects.getSize().x/16);
            tv = (rand()%2+18)/(Resources::texture.objects.getSize().y/16);
        }
        else
        {
            tu = (rand()%3+15)%(Resources::texture.objects.getSize().x/16);
            tv = (rand()%3+15)/(Resources::texture.objects.getSize().y/16);
        }

        m_body.setTextureRect(sf::IntRect(tu*16, tv*16, 16, 16));
        m_body.setTexture(Resources::texture.objects);
        m_body.setScale(sf::Vector2f(5.f, 5.f));
    }

    void
    Chest::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = &Resources::texture.objects;
        target.draw(m_body, states);
    }

    std::ifstream&
    Chest::operator<<(std::ifstream& file)
    {
        sf::Vector2i position;
        int type;

        try
        {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        m_type = (Type) type;
        m_item = getRandomItem();

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Chest::operator>>(std::ofstream& file)
    {
        file << 40                              << ' '
             << (int) m_body.getPosition().x/80 << ' '
             << (int) m_body.getPosition().y/80 << ' '
             << m_type                          << ' ';

        return file;
    }

}
