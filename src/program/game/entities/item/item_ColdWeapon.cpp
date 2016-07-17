/**
 * @file src/program/game/item/item_ColdWeapon.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "item_ColdWeapon.hpp"
#include "../../../program.hpp"
#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

extern rr::Resources resources;

namespace rr {

    ColdWeapon::ColdWeapon(Type type, int amount, sf::Vector2i pos)
    : Equipable(    ),
      level_   (0   ),
      type_    (type) {

        amount_     = amount;

        initialize();
        setPosition(pos);
    }

    ColdWeapon::ColdWeapon(ColdWeapon const& coldWeapon)
    : Equipable(                ),
      type_    (coldWeapon.type_) {

        amount_                = coldWeapon.amount_;
        disposable_            = coldWeapon.disposable_;
        stackable_             = coldWeapon.stackable_;
        ID_                    = coldWeapon.ID_;
        iconIndex_             = coldWeapon.iconIndex_;
        name_                  = coldWeapon.name_;
        description_           = coldWeapon.description_;
        discoveredName_        = coldWeapon.discoveredName_;
        discoveredDescription_ = coldWeapon.discoveredDescription_;
        body_                  = coldWeapon.body_;
    }

    void ColdWeapon::initialize() {
        disposable_ = false;
        stackable_  = false;
        ID_         = 10+type_;

        switch (type_) {
        case HAMMER:         damageDealt_      = 70;
                             strengthRequired_ = 80;
                             speed_            =  4;
                             accuracy_         = 10;
                             name_             = resources.dictionary["item.coldweapon.name.hammer"               ];
                             description_      = resources.dictionary["item.coldweapon.description.hammer"        ];
                             iconIndex_        = 39;
                             break;

        case DOUBLE_AXE:     damageDealt_      =  90;
                             strengthRequired_ = 100;
                             speed_            =   5;
                             accuracy_         =   7;
                             name_             = resources.dictionary["item.coldweapon.name.double_axe"           ];
                             description_      = resources.dictionary["item.coldweapon.description.double_axe"    ];
                             iconIndex_        = 21;
                             break;

        case HALBERD:        damageDealt_      = 60;
                             strengthRequired_ = 70;
                             speed_            =  4;
                             accuracy_         =  7;
                             name_             = resources.dictionary["item.coldweapon.name.halberd"              ];
                             description_      = resources.dictionary["item.coldweapon.description.halberd"       ];
                             iconIndex_        = 22;
                             break;

        case AXE:            damageDealt_      = 55;
                             strengthRequired_ = 70;
                             speed_            =  7;
                             accuracy_         =  5;
                             name_             = resources.dictionary["item.coldweapon.name.axe"                  ];
                             description_      = resources.dictionary["item.coldweapon.description.axe"           ];
                             iconIndex_        = 20;
                             break;

        case SERRATED_SWORD: damageDealt_      = 50;
                             strengthRequired_ = 60;
                             speed_            =  7;
                             accuracy_         =  8;
                             name_             = resources.dictionary["item.coldweapon.name.serrated_sword"       ];
                             description_      = resources.dictionary["item.coldweapon.description.serrated_sword"];
                             iconIndex_        =  7;
                             break;

        case LANCE:          damageDealt_      = 50;
                             strengthRequired_ = 60;
                             speed_            =  4;
                             accuracy_         =  6;
                             name_             = resources.dictionary["item.coldweapon.name.lance"                ];
                             description_      = resources.dictionary["item.coldweapon.description.lance"         ];
                             iconIndex_        = 24;
                             break;

        case CLUB:           damageDealt_      = 40;
                             strengthRequired_ = 50;
                             speed_            =  6;
                             accuracy_         =  7;
                             name_             = resources.dictionary["item.coldweapon.name.club"                 ];
                             description_      = resources.dictionary["item.coldweapon.description.club"          ];
                             iconIndex_        = 38;
                             break;
                             
        case SWORD:          damageDealt_      = 30;
                             strengthRequired_ = 30;
                             speed_            =  7;
                             accuracy_         =  5;
                             name_             = resources.dictionary["item.coldweapon.name.sword"                ];
                             description_      = resources.dictionary["item.coldweapon.description.sword"         ];
                             iconIndex_        =  6;
                             break;

        case SPEAR:          damageDealt_      = 30;
                             strengthRequired_ = 50;
                             speed_            =  6;
                             accuracy_         =  4;
                             name_             = resources.dictionary["item.coldweapon.name.spear"                ];
                             description_      = resources.dictionary["item.coldweapon.description.spear"         ];
                             iconIndex_        = 23;
                             break;

        case PIQUE:          damageDealt_      = 20;
                             strengthRequired_ = 25;
                             speed_            =  7;
                             accuracy_         =  7;
                             name_             = resources.dictionary["item.coldweapon.name.pique"                ];
                             description_      = resources.dictionary["item.coldweapon.description.pique"         ];
                             iconIndex_        = 36;
                             break;

        case LONG_STICK:     damageDealt_      = 15;
                             strengthRequired_ = 20;
                             speed_            =  8;
                             accuracy_         =  7;
                             name_             = resources.dictionary["item.coldweapon.name.long_stick"           ];
                             description_      = resources.dictionary["item.coldweapon.description.long_stick"    ];
                             iconIndex_        = 37;
                             break;

        case DAGGER:         damageDealt_      = 15;
                             strengthRequired_ =  5;
                             speed_            =  8;
                             accuracy_         =  5;
                             name_             = resources.dictionary["item.coldweapon.name.dagger"               ];
                             description_      = resources.dictionary["item.coldweapon.description.dagger"        ];
                             iconIndex_        =  5;
                             break;
                             
        case KNIFE:          damageDealt_      = 10;
                             strengthRequired_ =  5;
                             speed_            = 10;
                             accuracy_         =  4;
                             name_             = resources.dictionary["item.coldweapon.name.knife"                ];
                             description_      = resources.dictionary["item.coldweapon.description.knife"         ];
                             iconIndex_        =  4;
                             break;
        }

        setIcon    (body_, iconIndex_);
    }

    void ColdWeapon::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void ColdWeapon::enhance() {
        level_            ++;
        speed_            ++;
        accuracy_         ++;
        damageDealt_      += 5;
        strengthRequired_ -= 3;
    }

    void ColdWeapon::enchant() {

    }

    sf::String ColdWeapon::getDescription() const {
        return description_ +              "\n"+resources.dictionary["item.coldweapon.strength_required"]+" "+std::to_string((int)strengthRequired_)
                            +              "\n"+resources.dictionary["item.coldweapon.damage_dealt"     ]+" "+std::to_string((int)damageDealt_)
                            + ((level_!=0)?"\n"+resources.dictionary["item.coldweapon.level"            ]+" "+std::to_string((int)level_):"");
    }

    std::ifstream& ColdWeapon::operator<<(std::ifstream& file) {
        sf::Vector2i position;
        int type;

        try {
            readFile  <int>  (file, position.x);
            readFile  <int>  (file, position.y);
            readFile  <int>  (file, amount_);
            readFile  <bool> (file, discovered_);
            readFile  <bool> (file, equipped_);
            readFile  <int>  (file, level_);                        
            readFile  <int>  (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();

        speed_            += level_;
        accuracy_         += level_;
        damageDealt_      += level_*5;
        strengthRequired_ -= level_*3;

        setPosition(position);

        return file;
    }

    std::ofstream& ColdWeapon::operator>>(std::ofstream& file) {
        file << 4                           << ' '
             << (int)body_[0].position.x/80 << ' '
             << (int)body_[0].position.y/80 << ' '
             << amount_                     << ' '
             << discovered_                 << ' '
             << equipped_                   << ' '
             << level_                      << ' '
             << type_;

        return file;
    }

}

