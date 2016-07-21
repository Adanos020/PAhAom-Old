/**
 * @file src/program/game/item/item_Rune.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "item_Rune.hpp"
#include "../../../program.hpp"
#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"

extern rr::Resources resources;
extern int           spellSymbols[11];

namespace rr {

    bool Rune::identified_[12] = { false, false, false, false, false, false, false, false, false, false, false, false };

    Rune::Rune(Type type, int am, sf::Vector2i pos)
    : Discoverable(    ),
      type_       (type) {

        amount_     = am;

        initialize();
        setPosition(pos);
    }

    Rune::Rune(Rune const& rune)
    : Discoverable(          ),
      type_       (rune.type_) {

        amount_                = rune.amount_;
        disposable_            = rune.disposable_;
        stackable_             = rune.stackable_;
        ID_                    = rune.ID_;
        iconIndex_             = rune.iconIndex_;
        body_                  = rune.body_;
    }

    void Rune::initialize() {
        disposable_ = true;
        stackable_  = true;
        cursed_     = chance(2, 5);
        ID_         = 39+type_;
        iconIndex_  = 48;

        int icons[] = { (int)iconIndex_, 64+(int)spellSymbols[type_] };

        setIcon    (body_, 2, icons);
    }

    void Rune::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    sf::String Rune::getName() const {
        if (!identified_[type_]) {
            switch (spellSymbols[type_]) {
                case  0: return resources.dictionary["item.spell.symbol.shcha"  ];
                case  1: return resources.dictionary["item.spell.symbol.jus"    ];
                case  2: return resources.dictionary["item.spell.symbol.jes"    ];
                case  3: return resources.dictionary["item.spell.symbol.ef"     ];
                case  4: return resources.dictionary["item.spell.symbol.ju"     ];
                case  5: return resources.dictionary["item.spell.symbol.psi"    ];
                case  6: return resources.dictionary["item.spell.symbol.de"     ];
                case  7: return resources.dictionary["item.spell.symbol.omega"  ];
                case  8: return resources.dictionary["item.spell.symbol.je"     ];
                case  9: return resources.dictionary["item.spell.symbol.zhe"    ];
                case 10: return resources.dictionary["item.spell.symbol.be"     ];
                case 11: return resources.dictionary["item.spell.symbol.izhitsa"];
            }
        }
        else {
            switch (type_) {
                case HEAL         : return resources.dictionary["item.spell.type.heal"        ];
                case FIREBOLT     : return resources.dictionary["item.spell.type.firebolt"    ];
                case LIGHTNING    : return resources.dictionary["item.spell.type.lightning"   ];
                case ICE_BULLET   : return resources.dictionary["item.spell.type.iceBullet"   ];
                case TELEPORT     : return resources.dictionary["item.spell.type.teleport"    ];
                case FIRE_RAIN    : return resources.dictionary["item.spell.type.fireRain"    ];
                case STORM        : return resources.dictionary["item.spell.type.storm"       ];
                case ICE_WAVE     : return resources.dictionary["item.spell.type.iceWave"     ];
                case TIME_FREEZING: return resources.dictionary["item.spell.type.timeFreezing"];
                case IDENTIFY     : return resources.dictionary["item.spell.type.identify"    ];
                case UNCURSE      : return resources.dictionary["item.spell.type.uncurse"     ];
                case TELEKINESIS  : return resources.dictionary["item.spell.type.telekinesis" ];
            }
        }
        return "";
    }

    sf::String Rune::getDescription() const {
        if ( !identified_[type_]
            ) return resources.dictionary["item.spell.description.unknown"];
        else {
            switch (type_) {
                case HEAL         : return resources.dictionary["item.spell.description.heal"        ];
                case FIREBOLT     : return resources.dictionary["item.spell.description.firebolt"    ];
                case LIGHTNING    : return resources.dictionary["item.spell.description.lightning"   ];
                case ICE_BULLET   : return resources.dictionary["item.spell.description.iceBullet"   ];
                case TELEPORT     : return resources.dictionary["item.spell.description.teleport"    ];
                case FIRE_RAIN    : return resources.dictionary["item.spell.description.fireRain"    ];
                case STORM        : return resources.dictionary["item.spell.description.storm"       ];
                case ICE_WAVE     : return resources.dictionary["item.spell.description.iceWave"     ];
                case TIME_FREEZING: return resources.dictionary["item.spell.description.timeFreezing"];
                case IDENTIFY     : return resources.dictionary["item.spell.description.identify"    ];
                case UNCURSE      : return resources.dictionary["item.spell.description.uncurse"     ];
                case TELEKINESIS  : return resources.dictionary["item.spell.description.telekinesis" ];
            }
        }
        return "";
    }

    void Rune::setPosition(sf::Vector2i pos) {
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    void Rune::setRealPosition(sf::Vector2f pos) {
        body_[0].position = pos;
        body_[1].position = sf::Vector2f(pos.x+80, pos.y   );
        body_[2].position = sf::Vector2f(pos.x+80, pos.y+80);
        body_[3].position = sf::Vector2f(pos.x   , pos.y+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    std::ifstream& Rune::operator<<(std::ifstream& file) {
        sf::Vector2i position;
        int type;

        try {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, amount_);                 
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();
        setPosition(position);

        return file;
    }

    std::ofstream& Rune::operator>>(std::ofstream& file) {
        file << 8                           << ' '
             << (int)body_[0].position.x/80 << ' '
             << (int)body_[0].position.y/80 << ' '
             << amount_                     << ' '
             << type_;

        return file;
    }

}
