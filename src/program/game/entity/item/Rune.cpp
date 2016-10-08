/**
 * @file src/program/game/item/Rune.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Rune.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"

extern int spellSymbols[12];

namespace rr
{

    bool Rune::m_identified[12] = { false, false, false, false, false, false, false, false, false, false, false, false };

    Rune::Rune(Type type, int am, sf::Vector2i pos) :
      m_type(type)
    {
        m_amount = am;

        initialize();
        setGridPosition(pos);
    }

    Rune::Rune(Rune const& copy) :
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
    Rune::initialize()
    {
        m_disposable = true;
        m_stackable  = true;
        m_cursed     = chance(2, 5);
        m_ID         = 49+m_type;
        m_iconIndex  = 48;

        int icons[] = { (int) m_iconIndex, 64 + (int) spellSymbols[m_type] };

        setIcon(m_body, 2, icons);
    }

    sf::String
    Rune::getName() const
    {
        if (!m_identified[m_type])
        {
            switch (spellSymbols[m_type])
            {
                case  0: return Resources::dictionary["item.spell.symbol.shcha"  ];
                case  1: return Resources::dictionary["item.spell.symbol.jus"    ];
                case  2: return Resources::dictionary["item.spell.symbol.jes"    ];
                case  3: return Resources::dictionary["item.spell.symbol.ef"     ];
                case  4: return Resources::dictionary["item.spell.symbol.ju"     ];
                case  5: return Resources::dictionary["item.spell.symbol.psi"    ];
                case  6: return Resources::dictionary["item.spell.symbol.de"     ];
                case  7: return Resources::dictionary["item.spell.symbol.omega"  ];
                case  8: return Resources::dictionary["item.spell.symbol.je"     ];
                case  9: return Resources::dictionary["item.spell.symbol.zhe"    ];
                case 10: return Resources::dictionary["item.spell.symbol.be"     ];
                case 11: return Resources::dictionary["item.spell.symbol.izhitsa"];
            }
        }
        else
        {
            switch (m_type)
            {
                case HEAL         : return Resources::dictionary["item.spell.type.heal"        ];
                case FIREBOLT     : return Resources::dictionary["item.spell.type.firebolt"    ];
                case LIGHTNING    : return Resources::dictionary["item.spell.type.lightning"   ];
                case ICE_BULLET   : return Resources::dictionary["item.spell.type.iceBullet"   ];
                case TELEPORT     : return Resources::dictionary["item.spell.type.teleport"    ];
                case FIRE_RAIN    : return Resources::dictionary["item.spell.type.fireRain"    ];
                case STORM        : return Resources::dictionary["item.spell.type.storm"       ];
                case ICE_WAVE     : return Resources::dictionary["item.spell.type.iceWave"     ];
                case TIME_FREEZING: return Resources::dictionary["item.spell.type.timeFreezing"];
                case IDENTIFY     : return Resources::dictionary["item.spell.type.identify"    ];
                case UNCURSE      : return Resources::dictionary["item.spell.type.uncurse"     ];
                case TELEKINESIS  : return Resources::dictionary["item.spell.type.telekinesis" ];
            }
        }
        return "";
    }

    sf::String
    Rune::getDescription() const
    {
        if (!m_identified[m_type])
            return Resources::dictionary["item.spell.description.unknown"];
        else
        {
            switch (m_type)
            {
                case HEAL         : return Resources::dictionary["item.spell.description.heal"        ];
                case FIREBOLT     : return Resources::dictionary["item.spell.description.firebolt"    ];
                case LIGHTNING    : return Resources::dictionary["item.spell.description.lightning"   ];
                case ICE_BULLET   : return Resources::dictionary["item.spell.description.iceBullet"   ];
                case TELEPORT     : return Resources::dictionary["item.spell.description.teleport"    ];
                case FIRE_RAIN    : return Resources::dictionary["item.spell.description.fireRain"    ];
                case STORM        : return Resources::dictionary["item.spell.description.storm"       ];
                case ICE_WAVE     : return Resources::dictionary["item.spell.description.iceWave"     ];
                case TIME_FREEZING: return Resources::dictionary["item.spell.description.timeFreezing"];
                case IDENTIFY     : return Resources::dictionary["item.spell.description.identify"    ];
                case UNCURSE      : return Resources::dictionary["item.spell.description.uncurse"     ];
                case TELEKINESIS  : return Resources::dictionary["item.spell.description.telekinesis" ];
            }
        }
        return "";
    }

    void
    Rune::setGridPosition(sf::Vector2i pos)
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
    Rune::setPosition(sf::Vector2f pos)
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
    Rune::operator<<(std::ifstream& file)
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
    Rune::operator>>(std::ofstream& file)
    {
        file << 7                             << ' '
             << (int) m_body[0].position.x/80 << ' '
             << (int) m_body[0].position.y/80 << ' '
             << m_amount                      << ' '
             << m_type;

        return file;
    }

}
