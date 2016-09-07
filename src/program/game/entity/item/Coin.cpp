/**
 * @file src/program/game/item/Coin.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Coin.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

namespace rr
{

    Coin::Coin(Type t, Size s, int am, sf::Vector2i pos) :
      m_type(t),
      m_size(s)
    {
        m_amount = am;

        initialize();
        setGridPosition(pos);
    }

    Coin::Coin(Coin const& copy) :
      m_type(copy.m_type),
      m_size(copy.m_size)
    {
        m_amount     = copy.m_amount;
        m_disposable = copy.m_disposable;
        m_stackable  = copy.m_stackable;
        m_ID         = copy.m_ID;
        m_iconIndex  = copy.m_iconIndex;
        m_body       = copy.m_body;
    }

    void
    Coin::initialize()
    {
        m_disposable = false;
        m_stackable  = true;
        m_cursed     = false;
        m_ID         = 3*m_size + m_type + 1;
        m_iconIndex  = m_type + (m_size+2)*16 + 1;

        setIcon(m_body, m_iconIndex);
    }
    
    sf::String
    Coin::getName() const
    {
        switch (m_type)
        {
            case BRONZE: return Resources::dictionary["item.coin.bronze"];
            case SILVER: return Resources::dictionary["item.coin.silver"];
            case GOLDEN: return Resources::dictionary["item.coin.gold"  ];
        }
        return "";
    }

    sf::String
    Coin::getDescription() const
    {
        return "";
    }

    std::ifstream&
    Coin::operator<<(std::ifstream& file)
    {
        sf::Vector2i position;
        int type, size;

        try
        {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, m_amount);
            readFile <int> (file, type);
            readFile <int> (file, size);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        m_type = (Type) type;
        m_size = (Size) size;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Coin::operator>>(std::ofstream& file)
    {
        file << 2                             << ' '
             << (int) m_body[0].position.x/80 << ' '
             << (int) m_body[0].position.y/80 << ' '
             << m_amount                      << ' '
             << m_type                        << ' '
             << m_size;

        return file;
    }

}
