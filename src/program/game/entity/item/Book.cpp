/**
 * @file src/program/game/item/Book.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Book.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

extern sf::Color itemColors[9];

namespace rr
{

    Book::Book(Type type, int am, sf::Vector2i pos) {
        m_type       = type;
        m_amount     = am;

        initialize();
        setGridPosition(pos);
    }

    Book::Book(Book const& copy) :
      m_type(copy.m_type)
    {
        m_amount      = copy.m_amount;
        m_disposable  = copy.m_disposable;
        m_stackable   = copy.m_stackable;
        m_ID          = copy.m_ID;
        m_iconIndex   = copy.m_iconIndex;
        m_body        = copy.m_body;
    }

    void
    Book::initialize()
    {
        m_ID         = m_type+40;
        m_stackable  = false;
        m_cursed     = false;
        m_iconIndex  = 16;

        m_disposable = m_type != SPELLS_BOOK;

        int icons[] = { (int) m_iconIndex, icons[1] = (int) m_iconIndex+16 };

        setIcon (m_body, 2, icons);
        setColor(m_body, 0, sf::Color(itemColors[m_type].r + (255-itemColors[m_type].r)/2,
                                     itemColors[m_type].g + (255-itemColors[m_type].g)/2,
                                     itemColors[m_type].b + (255-itemColors[m_type].b)/2));
    }

    sf::String
    Book::getName() const
    {
        switch (m_type)
        {
            case CRAFTING:              return Resources::dictionary["item.book.type.crafting"             ];
            case ALCHEMY:               return Resources::dictionary["item.book.type.alchemy"              ];
            case MELEE_WEAPON_MASTERY:  return Resources::dictionary["item.book.type.melee_weapon_mastery" ];
            case RANGED_WEAPON_MASTERY: return Resources::dictionary["item.book.type.ranged_weapon_mastery"];
            case EAGLE_EYE:             return Resources::dictionary["item.book.type.eagle_eye"            ];
            case MANA_REGEN:            return Resources::dictionary["item.book.type.mana_regen"           ];
            case HEALTH_REGEN:          return Resources::dictionary["item.book.type.health_regen"         ];
            case FASTER_LEARNING:       return Resources::dictionary["item.book.type.faster_learning"      ];
            case SPELLS_BOOK:           return Resources::dictionary["item.book.type.spells_book"          ];
        }
        return "";
    }

    sf::String
    Book::getDescription() const
    {
        switch (m_type)
        {
            case CRAFTING:              return Resources::dictionary["item.book.description.crafting"             ];
            case ALCHEMY:               return Resources::dictionary["item.book.description.alchemy"              ];
            case MELEE_WEAPON_MASTERY:  return Resources::dictionary["item.book.description.melee_weapon_mastery" ];
            case RANGED_WEAPON_MASTERY: return Resources::dictionary["item.book.description.ranged_weapon_mastery"];
            case EAGLE_EYE:             return Resources::dictionary["item.book.description.eagle_eye"            ];
            case MANA_REGEN:            return Resources::dictionary["item.book.description.mana_regen"           ];
            case HEALTH_REGEN:          return Resources::dictionary["item.book.description.health_regen"         ];
            case FASTER_LEARNING:       return Resources::dictionary["item.book.description.faster_learning"      ];
            case SPELLS_BOOK:           return Resources::dictionary["item.book.description.spells_book"          ];
        }
        return "";
    }

    void
    Book::setGridPosition(sf::Vector2i pos)
    {
        m_body[0].position = (sf::Vector2f)pos*80.f;
        m_body[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        m_body[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        m_body[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        m_body[4].position = m_body[0].position;
        m_body[5].position = m_body[1].position;
        m_body[6].position = m_body[2].position;
        m_body[7].position = m_body[3].position;
    }

    void
    Book::setPosition(sf::Vector2f pos)
    {
        m_body[0].position = pos;
        m_body[1].position = sf::Vector2f(pos.x+80, pos.y   );
        m_body[2].position = sf::Vector2f(pos.x+80, pos.y+80);
        m_body[3].position = sf::Vector2f(pos.x   , pos.y+80);

        m_body[4].position = m_body[0].position;
        m_body[5].position = m_body[1].position;
        m_body[6].position = m_body[2].position;
        m_body[7].position = m_body[3].position;
    }

    std::ifstream&
    Book::operator<<(std::ifstream& file)
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
    Book::operator>>(std::ofstream& file)
    {
        file << 1                             << ' '
             << (int) m_body[0].position.x/80 << ' '
             << (int) m_body[0].position.y/80 << ' '
             << m_amount                      << ' '
             << m_type;

        return file;
    }

}
