/**
 * @file src/program/game/item/Ammunition.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Ammunition.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

namespace rr
{

    Ammunition::Ammunition(Type type, int amount, sf::Vector2i position) :
      m_type(type)
    {
        m_amount = amount;

        initialize();
        setGridPosition(position);
    }

    Ammunition::Ammunition(Ammunition const& copy) :
      m_type(copy.m_type)
    {
        m_amount     = copy.m_amount;
        m_disposable = copy.m_disposable;
        m_stackable  = copy.m_stackable;
        m_ID         = copy.m_ID;
        m_iconIndex  = copy.m_iconIndex;
        m_body       = copy.m_body;
    }

    void
    Ammunition::initialize()
    {
        m_disposable = false;
        m_stackable  = true;
        m_cursed     = false;
        m_ID         = m_type + 27;
        m_iconIndex  = m_type + 56;

        setIcon(m_body, m_iconIndex);
    }

    sf::String
    Ammunition::getName() const
    {
        switch (m_type)
        {
            case ARROW   : return Resources::dictionary["item.ammunition.name.arrow"   ];
            case BOLT    : return Resources::dictionary["item.ammunition.name.bolt"    ];
            case ROCKS   : return Resources::dictionary["item.ammunition.name.rocks"   ];
            case DART    : return Resources::dictionary["item.ammunition.name.dart"    ];
            case SHURIKEN: return Resources::dictionary["item.ammunition.name.shuriken"];
        }

        return "";
    }

    sf::String
    Ammunition::getDescription() const
    {
        switch (m_type)
        {
            case ARROW   : return Resources::dictionary["item.ammunition.description.arrow"   ];
            case BOLT    : return Resources::dictionary["item.ammunition.description.bolt"    ];
            case ROCKS   : return Resources::dictionary["item.ammunition.description.rocks"   ];
            case DART    : return Resources::dictionary["item.ammunition.description.dart"    ];
            case SHURIKEN: return Resources::dictionary["item.ammunition.description.shuriken"];
        }

        return "";
    }

    std::ifstream&
    Ammunition::operator<<(std::ifstream& file)
    {
        sf::Vector2i position;
        int type;

        try
        {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, m_amount);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        m_type = (Type) type;

        initialize();

        setGridPosition(position);
        
        return file;
    }

    std::ofstream&
    Ammunition::operator>>(std::ofstream& file)
    {
        file << 0                             << ' '
             << (int) m_body[0].position.x/80 << ' '
             << (int) m_body[0].position.y/80 << ' '
             << m_amount                      << ' '
             << m_type;

        return file;
    }

}
