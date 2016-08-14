/**
 * @file src/program/game/item/ColdWeapon.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "ColdWeapon.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"

namespace rr {

    ColdWeapon::ColdWeapon(Type type, int amount, sf::Vector2i pos) :
      type_      (type )
    {
        level_      = 0;
        identified_ = false;
        amount_     = amount;

        initialize();
        setGridPosition(pos);
    }

    ColdWeapon::ColdWeapon(ColdWeapon const& copy) :
      type_(copy.type_)
    {
        amount_     = copy.amount_;
        disposable_ = copy.disposable_;
        stackable_  = copy.stackable_;
        ID_         = copy.ID_;
        iconIndex_  = copy.iconIndex_;
        body_       = copy.body_;
    }

    void ColdWeapon::initialize() {
        disposable_ = false;
        stackable_  = false;
        cursed_     = chance(1, 4);
        ID_         = 10+type_;

        switch (type_) {
            case HAMMER:         damageDealt_ = 70;
                                 requirement_ = 80;
                                 speed_       =  4;
                                 accuracy_    = 10;
                                 iconIndex_   = 39;
                                 break;

            case DOUBLE_AXE:     damageDealt_ =  90;
                                 requirement_ = 100;
                                 speed_       =   5;
                                 accuracy_    =   7;
                                 iconIndex_   =  21;
                                 break;

            case HALBERD:        damageDealt_ = 60;
                                 requirement_ = 70;
                                 speed_       =  4;
                                 accuracy_    =  7;
                                 iconIndex_   = 22;
                                 break;

            case AXE:            damageDealt_ = 55;
                                 requirement_ = 70;
                                 speed_       =  7;
                                 accuracy_    =  5;
                                 iconIndex_   = 20;
                                 break;

            case SERRATED_SWORD: damageDealt_ = 50;
                                 requirement_ = 60;
                                 speed_       =  7;
                                 accuracy_    =  8;
                                 iconIndex_   =  7;
                                 break;

            case LANCE:          damageDealt_ = 50;
                                 requirement_ = 60;
                                 speed_       =  4;
                                 accuracy_    =  6;
                                 iconIndex_   = 24;
                                 break;

            case CLUB:           damageDealt_ = 40;
                                 requirement_ = 50;
                                 speed_       =  6;
                                 accuracy_    =  7;
                                 iconIndex_   = 38;
                                 break;
                             
            case SWORD:          damageDealt_ = 30;
                                 requirement_ = 30;
                                 speed_       =  7;
                                 accuracy_    =  5;
                                 iconIndex_   =  6;
                                 break;

            case SPEAR:          damageDealt_ = 30;
                                 requirement_ = 50;
                                 speed_       =  6;
                                 accuracy_    =  4;
                                 iconIndex_   = 23;
                                 break;

            case PIQUE:          damageDealt_ = 20;
                                 requirement_ = 25;
                                 speed_       =  7;
                                 accuracy_    =  7;
                                 iconIndex_   = 36;
                                 break;

            case LONG_STICK:     damageDealt_ = 15;
                                 requirement_ = 20;
                                 speed_       =  8;
                                 accuracy_    =  7;
                                 iconIndex_   = 37;
                                 break;

            case DAGGER:         damageDealt_ = 15;
                                 requirement_ =  5;
                                 speed_       =  8;
                                 accuracy_    =  5;
                                 iconIndex_   =  5;
                                 break;
                             
            case KNIFE:          damageDealt_ = 10;
                                 requirement_ =  5;
                                 speed_       = 10;
                                 accuracy_    =  4;
                                 iconIndex_   =  4;
                                 break;
        }

        setIcon    (body_, iconIndex_);
    }
    
    sf::String ColdWeapon::getName() const {
        sf::String name = "";

        switch (type_) {
            case HAMMER        : name += Resources::dictionary["item.coldweapon.name.hammer"        ]; break;
            case DOUBLE_AXE    : name += Resources::dictionary["item.coldweapon.name.double_axe"    ]; break;
            case HALBERD       : name += Resources::dictionary["item.coldweapon.name.halberd"       ]; break;
            case AXE           : name += Resources::dictionary["item.coldweapon.name.axe"           ]; break;
            case SERRATED_SWORD: name += Resources::dictionary["item.coldweapon.name.serrated_sword"]; break;
            case LANCE         : name += Resources::dictionary["item.coldweapon.name.lance"         ]; break;
            case CLUB          : name += Resources::dictionary["item.coldweapon.name.club"          ]; break;
            case SWORD         : name += Resources::dictionary["item.coldweapon.name.sword"         ]; break;
            case SPEAR         : name += Resources::dictionary["item.coldweapon.name.spear"         ]; break;
            case PIQUE         : name += Resources::dictionary["item.coldweapon.name.pique"         ]; break;
            case LONG_STICK    : name += Resources::dictionary["item.coldweapon.name.long_stick"    ]; break;
            case DAGGER        : name += Resources::dictionary["item.coldweapon.name.dagger"        ]; break;
            case KNIFE         : name += Resources::dictionary["item.coldweapon.name.knife"         ]; break;
        }

        name += ((identified_ && cursed_) ? " - "+Resources::dictionary["item.enchantment.name.cursed"] : "");
        
        return name;
    }

    sf::String ColdWeapon::getDescription() const {
        sf::String description = "";

        switch (type_) {
            case HAMMER        : description += Resources::dictionary["item.coldweapon.description.hammer"        ]; break;
            case DOUBLE_AXE    : description += Resources::dictionary["item.coldweapon.description.double_axe"    ]; break;
            case HALBERD       : description += Resources::dictionary["item.coldweapon.description.halberd"       ]; break;
            case AXE           : description += Resources::dictionary["item.coldweapon.description.axe"           ]; break;
            case SERRATED_SWORD: description += Resources::dictionary["item.coldweapon.description.serrated_sword"]; break;
            case LANCE         : description += Resources::dictionary["item.coldweapon.description.lance"         ]; break;
            case CLUB          : description += Resources::dictionary["item.coldweapon.description.club"          ]; break;
            case SWORD         : description += Resources::dictionary["item.coldweapon.description.sword"         ]; break;
            case SPEAR         : description += Resources::dictionary["item.coldweapon.description.spear"         ]; break;
            case PIQUE         : description += Resources::dictionary["item.coldweapon.description.pique"         ]; break;
            case LONG_STICK    : description += Resources::dictionary["item.coldweapon.description.long_stick"    ]; break;
            case DAGGER        : description += Resources::dictionary["item.coldweapon.description.dagger"        ]; break;
            case KNIFE         : description += Resources::dictionary["item.coldweapon.description.knife"         ]; break;
        }

        description += "\n" + ((identified_ && cursed_  ) ? "\n"+Resources::dictionary["item.enchantment.description.cursed"]                                 : "")
                            +                               "\n"+Resources::dictionary["item.requirement.strength"          ]+" "+std::to_string((int)requirement_)
                            +                               "\n"+Resources::dictionary["item.weapon.damage_dealt"           ]+" "+std::to_string((int)damageDealt_)
                            + ((identified_ && level_!=0) ? "\n"+Resources::dictionary["item.weapon.level"                  ]+" "+std::to_string((int)level_) : "");

        return description;
    }

    void ColdWeapon::enhance() {
        level_       ++;
        speed_       ++;
        accuracy_    ++;
        damageDealt_ += 5;
        requirement_ -= 3;
    }

    void ColdWeapon::enchant() {

    }

    std::ifstream& ColdWeapon::operator<<(std::ifstream& file) {
        sf::Vector2i position;
        int type;

        try {
            readFile <int > (file, position.x);
            readFile <int > (file, position.y);
            readFile <int > (file, amount_);
            readFile <bool> (file, identified_);
            readFile <bool> (file, equipped_);
            readFile <int > (file, level_);
            readFile <int > (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();

        speed_       += level_;
        accuracy_    += level_;
        damageDealt_ += level_*5;
        requirement_ -= level_*3;

        setGridPosition(position);

        return file;
    }

    std::ofstream& ColdWeapon::operator>>(std::ofstream& file) {
        file << 3                            << ' '
             << (int) body_[0].position.x/80 << ' '
             << (int) body_[0].position.y/80 << ' '
             << amount_                      << ' '
             << identified_                  << ' '
             << equipped_                    << ' '
             << level_                       << ' '
             << type_;

        return file;
    }

}

