/**
 * @file src/program/game/item/Food.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Food.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

namespace rr
{

    Food::Food(Type type, int amount, sf::Vector2i position) :
      m_type(type)
    {
        m_amount = amount;

        initialize();
        setGridPosition(position);
    }

    Food::Food(Food const& copy) :
      m_type(copy.m_type)
    {
        m_amount     = copy.m_amount;
        m_disposable = copy.m_disposable;
        m_stackable  = copy.m_stackable;
        m_ID         = copy.m_ID;
        m_iconIndex  = copy.m_iconIndex;
        m_body       = copy.m_body;
    }

    void Food::initialize()
    {
        m_disposable = true;
        m_stackable  = true;
        m_cursed     = false;
        m_ID         = m_type + 61;
        m_iconIndex  = m_type + 80;

        setIcon(m_body, m_iconIndex);
    }

    sf::String Food::getName() const
    {
        switch (m_type)
        {
            case MEAT     : return Resources::dictionary["item.food.name.meat"     ];
            case SANDVICH : return Resources::dictionary["item.food.name.sandvich" ];
            case APPLE    : return Resources::dictionary["item.food.name.apple"    ];
            case BEER     : return Resources::dictionary["item.food.name.beer"     ];
            case HOT_DOG  : return Resources::dictionary["item.food.name.hot_dog"  ];
            case HAMBURGER: return Resources::dictionary["item.food.name.hamburger"];
            case BAGUETTE : return Resources::dictionary["item.food.name.baguette" ];
        }
        return "";
    }

    sf::String Food::getDescription() const
    {
        switch (m_type)
        {
            case MEAT     : return Resources::dictionary["item.food.description.meat"     ];
            case SANDVICH : return Resources::dictionary["item.food.description.sandvich" ];
            case APPLE    : return Resources::dictionary["item.food.description.apple"    ];
            case BEER     : return Resources::dictionary["item.food.description.beer"     ];
            case HOT_DOG  : return Resources::dictionary["item.food.description.hot_dog"  ];
            case HAMBURGER: return Resources::dictionary["item.food.description.hamburger"];
            case BAGUETTE : return Resources::dictionary["item.food.description.baguette" ];
        }
        return "";
    }

    std::ifstream&
    Food::operator<<(std::ifstream& file)
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
    Food::operator>>(std::ofstream& file)
    {
        file << 4                             << ' '
             << (int) m_body[0].position.x/80 << ' '
             << (int) m_body[0].position.y/80 << ' '
             << m_amount                      << ' '
             << m_type;

        return file;
    }

}
