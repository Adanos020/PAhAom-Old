/**
 * @file src/program/game/item/Rune.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
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

    bool Rune::identified_[12] = { false, false, false, false, false, false, false, false, false, false, false, false };

    Rune::Rune(Type type, int am, sf::Vector2i pos) :
      type_ (type)
    {
        amount_     = am;

        initialize();
        setGridPosition(pos);
    }

    Rune::Rune(Rune const& copy) :
      type_ (copy.type_)
    {
        amount_     = copy.amount_;
        disposable_ = copy.disposable_;
        stackable_  = copy.stackable_;
        ID_         = copy.ID_;
        iconIndex_  = copy.iconIndex_;
        body_       = copy.body_;
    }

    void
    Rune::initialize()
    {
        disposable_ = true;
        stackable_  = true;
        cursed_     = chance(2, 5);
        ID_         = 49+type_;
        iconIndex_  = 48;

        int icons[] = { (int)iconIndex_, 64+(int)spellSymbols[type_] };

        setIcon(body_, 2, icons);
    }

    sf::String
    Rune::getName() const
    {
        if (!identified_[type_])
        {
            switch (spellSymbols[type_])
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
            switch (type_)
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
        if (!identified_[type_])
            return Resources::dictionary["item.spell.description.unknown"];
        else
        {
            switch (type_)
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
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    void
    Rune::setPosition(sf::Vector2f pos)
    {
        body_[0].position = pos;
        body_[1].position = sf::Vector2f(pos.x+80, pos.y   );
        body_[2].position = sf::Vector2f(pos.x+80, pos.y+80);
        body_[3].position = sf::Vector2f(pos.x   , pos.y+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
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
            readFile <int> (file, amount_);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Rune::operator>>(std::ofstream& file)
    {
        file << 7                            << ' '
             << (int) body_[0].position.x/80 << ' '
             << (int) body_[0].position.y/80 << ' '
             << amount_                      << ' '
             << type_;

        return file;
    }

}
