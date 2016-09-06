/**
 * @file src/program/game/item/MeleeWeapon.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "MeleeWeapon.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"

namespace rr
{

    MeleeWeapon::MeleeWeapon(Type type, int amount, sf::Vector2i pos) :
      type_(type )
    {
        level_      = 0;
        identified_ = false;
        amount_     = amount;

        initialize();
        setGridPosition(pos);
    }

    MeleeWeapon::MeleeWeapon(MeleeWeapon const& copy) :
      type_(copy.type_)
    {
        amount_     = copy.amount_;
        disposable_ = copy.disposable_;
        stackable_  = copy.stackable_;
        ID_         = copy.ID_;
        iconIndex_  = copy.iconIndex_;
        body_       = copy.body_;
    }

    void
    MeleeWeapon::initialize()
    {
        disposable_ = false;
        stackable_  = false;
        cursed_     = chance(1, 4);
        ID_         = 10+type_;

        switch (type_)
        {
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

        setIcon(body_, iconIndex_);
    }
    
    sf::String
    MeleeWeapon::getName() const
    {
        sf::String name = "";

        switch (type_)
        {
            case HAMMER        : name += Resources::dictionary["item.meleeweapon.name.hammer"        ]; break;
            case DOUBLE_AXE    : name += Resources::dictionary["item.meleeweapon.name.double_axe"    ]; break;
            case HALBERD       : name += Resources::dictionary["item.meleeweapon.name.halberd"       ]; break;
            case AXE           : name += Resources::dictionary["item.meleeweapon.name.axe"           ]; break;
            case SERRATED_SWORD: name += Resources::dictionary["item.meleeweapon.name.serrated_sword"]; break;
            case LANCE         : name += Resources::dictionary["item.meleeweapon.name.lance"         ]; break;
            case CLUB          : name += Resources::dictionary["item.meleeweapon.name.club"          ]; break;
            case SWORD         : name += Resources::dictionary["item.meleeweapon.name.sword"         ]; break;
            case SPEAR         : name += Resources::dictionary["item.meleeweapon.name.spear"         ]; break;
            case PIQUE         : name += Resources::dictionary["item.meleeweapon.name.pique"         ]; break;
            case LONG_STICK    : name += Resources::dictionary["item.meleeweapon.name.long_stick"    ]; break;
            case DAGGER        : name += Resources::dictionary["item.meleeweapon.name.dagger"        ]; break;
            case KNIFE         : name += Resources::dictionary["item.meleeweapon.name.knife"         ]; break;
        }

        name += ((identified_ && cursed_) ? " - "+Resources::dictionary["item.enchantment.name.cursed"] : "");
        
        return name;
    }

    sf::String
    MeleeWeapon::getDescription() const
    {
        sf::String description = "";

        switch (type_)
        {
            case HAMMER        : description += Resources::dictionary["item.meleeweapon.description.hammer"        ]; break;
            case DOUBLE_AXE    : description += Resources::dictionary["item.meleeweapon.description.double_axe"    ]; break;
            case HALBERD       : description += Resources::dictionary["item.meleeweapon.description.halberd"       ]; break;
            case AXE           : description += Resources::dictionary["item.meleeweapon.description.axe"           ]; break;
            case SERRATED_SWORD: description += Resources::dictionary["item.meleeweapon.description.serrated_sword"]; break;
            case LANCE         : description += Resources::dictionary["item.meleeweapon.description.lance"         ]; break;
            case CLUB          : description += Resources::dictionary["item.meleeweapon.description.club"          ]; break;
            case SWORD         : description += Resources::dictionary["item.meleeweapon.description.sword"         ]; break;
            case SPEAR         : description += Resources::dictionary["item.meleeweapon.description.spear"         ]; break;
            case PIQUE         : description += Resources::dictionary["item.meleeweapon.description.pique"         ]; break;
            case LONG_STICK    : description += Resources::dictionary["item.meleeweapon.description.long_stick"    ]; break;
            case DAGGER        : description += Resources::dictionary["item.meleeweapon.description.dagger"        ]; break;
            case KNIFE         : description += Resources::dictionary["item.meleeweapon.description.knife"         ]; break;
        }

        description += "\n" + ((identified_ && cursed_  ) ? "\n"+Resources::dictionary["item.enchantment.description.cursed"]                                 : "")
                            +                               "\n"+Resources::dictionary["item.requirement.strength"          ]+" "+std::to_string((int)requirement_)
                            +                               "\n"+Resources::dictionary["item.weapon.damage_dealt"           ]+" "+std::to_string((int)damageDealt_)
                            + ((identified_ && level_!=0) ? "\n"+Resources::dictionary["item.weapon.level"                  ]+" "+std::to_string((int)level_) : "");

        return description;
    }

    void
    MeleeWeapon::enhance()
    {
        level_       ++;
        speed_       ++;
        accuracy_    ++;
        damageDealt_ += 5;
        requirement_ -= 3;
    }

    void
    MeleeWeapon::enchant() 
    {

    }

    std::ifstream&
    MeleeWeapon::operator<<(std::ifstream& file)
    {
        sf::Vector2i position;
        int type;

        try
        {
            readFile <int > (file, position.x);
            readFile <int > (file, position.y);
            readFile <int > (file, amount_);
            readFile <bool> (file, identified_);
            readFile <bool> (file, equipped_);
            readFile <int > (file, level_);
            readFile <int > (file, type);
        }
        catch (std::invalid_argument ex)
        {
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

    std::ofstream&
    MeleeWeapon::operator>>(std::ofstream& file)
    {
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

