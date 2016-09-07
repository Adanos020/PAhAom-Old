/**
 * @file src/program/game/item/Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Potion.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

extern sf::Color itemColors[9];

namespace rr
{

    bool Potion::m_identified[9] = { false, false, false, false, false, false, false, false, false };

    Potion::Potion(Type e, Size s, int am, sf::Vector2i pos) :
      m_type(e),
      m_size(s)
    {
        m_amount = am;
        
        initialize();
        setGridPosition(pos);
    }

    Potion::Potion(Potion const& copy) :
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
    Potion::initialize()
    {
        m_disposable = true;
        m_stackable  = true;
        m_cursed     = false;
        m_ID         = 100 + m_type*10 + m_size;
        m_iconIndex  = 3-m_size;

        int icons[] = { (int) m_iconIndex, (int) m_iconIndex+16 };

        setIcon (m_body, 2, icons);
        setColor(m_body, 1, itemColors[m_type]);
    }

    sf::String
    Potion::getName() const
    {
        if (!m_identified[m_type])
        {
                 if (itemColors[m_type] == sf::Color::Red          ) return Resources::dictionary["item.potion.color.red"    ];
            else if (itemColors[m_type] == sf::Color::Blue         ) return Resources::dictionary["item.potion.color.blue"   ];
            else if (itemColors[m_type] == sf::Color(32, 32, 0)    ) return Resources::dictionary["item.potion.color.brown"  ];
            else if (itemColors[m_type] == sf::Color::Green        ) return Resources::dictionary["item.potion.color.green"  ];
            else if (itemColors[m_type] == sf::Color::Cyan         ) return Resources::dictionary["item.potion.color.cyan"   ];
            else if (itemColors[m_type] == sf::Color(255, 172, 172)) return Resources::dictionary["item.potion.color.pink"   ];
            else if (itemColors[m_type] == sf::Color::Magenta      ) return Resources::dictionary["item.potion.color.magenta"];
            else if (itemColors[m_type] == sf::Color::Yellow       ) return Resources::dictionary["item.potion.color.yellow" ];
            else if (itemColors[m_type] == sf::Color::White        ) return Resources::dictionary["item.potion.color.white"  ];
        }
        else
        {
            switch (m_type)
            {
                case HEALING:      return Resources::dictionary["item.potion.effect.healing"     ];
                case MAGIC:        return Resources::dictionary["item.potion.effect.magic"       ];
                case STRENGTH:     return Resources::dictionary["item.potion.effect.strength"    ];
                case DEXTERITY:    return Resources::dictionary["item.potion.effect.dexterity"   ];
                case SPEED:        return Resources::dictionary["item.potion.effect.speed"       ];
                case REGENERATION: return Resources::dictionary["item.potion.effect.regeneration"];
                case POISON:       return Resources::dictionary["item.potion.effect.poison"      ];
                case SLOWNESS:     return Resources::dictionary["item.potion.effect.slowness"    ];
                case WEAKNESS:     return Resources::dictionary["item.potion.effect.weakness"    ];
            }
        }
        return "";
    }

    sf::String
    Potion::getDescription() const
    {
        if (!m_identified[m_type])
            return Resources::dictionary["item.potion.description.unknown"];
        else
        {
            switch (m_type)
            {
                case HEALING     : return Resources::dictionary["item.potion.description.healing"     ];
                case MAGIC       : return Resources::dictionary["item.potion.description.magic"       ];
                case STRENGTH    : return Resources::dictionary["item.potion.description.strength"    ];
                case DEXTERITY   : return Resources::dictionary["item.potion.description.dexterity"   ];
                case SPEED       : return Resources::dictionary["item.potion.description.speed"       ];
                case REGENERATION: return Resources::dictionary["item.potion.description.regeneration"];
                case POISON      : return Resources::dictionary["item.potion.description.poison"      ];
                case SLOWNESS    : return Resources::dictionary["item.potion.description.slowness"    ];
                case WEAKNESS    : return Resources::dictionary["item.potion.description.weakness"    ];
            }
        }
        return "";
    }

    void
    Potion::setGridPosition(sf::Vector2i pos)
    {
        m_body[0].position = (sf::Vector2f) pos*80.f;
        m_body[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        m_body[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        m_body[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        m_body[4].position = m_body[0].position;
        m_body[5].position = m_body[1].position;
        m_body[6].position = m_body[2].position;
        m_body[7].position = m_body[3].position;
    }

    void
    Potion::setPosition(sf::Vector2f pos)
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
    Potion::operator<<(std::ifstream& file)
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
    Potion::operator>>(std::ofstream& file)
    {
        file << 5                             << ' '
             << (int) m_body[0].position.x/80 << ' '
             << (int) m_body[0].position.y/80 << ' '
             << m_amount                      << ' '
             << m_type                        << ' '
             << m_size;

        return file;
    }

}
