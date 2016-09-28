/**
 * @file src/program/game/item/MeleeWeapon.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
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
      m_type(type)
    {
        m_level      = 0;
        m_identified = false;
        m_amount     = amount;

        initialize();
        setGridPosition(pos);
    }

    MeleeWeapon::MeleeWeapon(MeleeWeapon const& copy) :
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
    MeleeWeapon::initialize()
    {
        m_disposable = false;
        m_stackable  = false;
        m_cursed     = chance(1, 4);
        m_ID         = 10 + m_type;

        switch (m_type)
        {
            case HAMMER:         m_damageDealt = 70;
                                 m_requirement = 80;
                                 m_speed       =  4;
                                 m_accuracy    = 10;
                                 m_iconIndex   = 39;
                                 break;

            case DOUBLE_AXE:     m_damageDealt =  90;
                                 m_requirement = 100;
                                 m_speed       =   5;
                                 m_accuracy    =   7;
                                 m_iconIndex   =  21;
                                 break;

            case HALBERD:        m_damageDealt = 60;
                                 m_requirement = 70;
                                 m_speed       =  4;
                                 m_accuracy    =  7;
                                 m_iconIndex   = 22;
                                 break;

            case AXE:            m_damageDealt = 55;
                                 m_requirement = 70;
                                 m_speed       =  7;
                                 m_accuracy    =  5;
                                 m_iconIndex   = 20;
                                 break;

            case SERRATED_SWORD: m_damageDealt = 50;
                                 m_requirement = 60;
                                 m_speed       =  7;
                                 m_accuracy    =  8;
                                 m_iconIndex   =  7;
                                 break;

            case LANCE:          m_damageDealt = 50;
                                 m_requirement = 60;
                                 m_speed       =  4;
                                 m_accuracy    =  6;
                                 m_iconIndex   = 24;
                                 break;

            case CLUB:           m_damageDealt = 40;
                                 m_requirement = 50;
                                 m_speed       =  6;
                                 m_accuracy    =  7;
                                 m_iconIndex   = 38;
                                 break;
                             
            case SWORD:          m_damageDealt = 30;
                                 m_requirement = 30;
                                 m_speed       =  7;
                                 m_accuracy    =  7;
                                 m_iconIndex   =  6;
                                 break;

            case SPEAR:          m_damageDealt = 30;
                                 m_requirement = 50;
                                 m_speed       =  6;
                                 m_accuracy    =  6;
                                 m_iconIndex   = 23;
                                 break;

            case PIQUE:          m_damageDealt = 20;
                                 m_requirement = 25;
                                 m_speed       =  7;
                                 m_accuracy    =  7;
                                 m_iconIndex   = 36;
                                 break;

            case LONG_STICK:     m_damageDealt = 15;
                                 m_requirement = 20;
                                 m_speed       =  8;
                                 m_accuracy    =  7;
                                 m_iconIndex   = 37;
                                 break;

            case DAGGER:         m_damageDealt = 15;
                                 m_requirement =  5;
                                 m_speed       =  8;
                                 m_accuracy    =  6;
                                 m_iconIndex   =  5;
                                 break;
                             
            case KNIFE:          m_damageDealt = 10;
                                 m_requirement =  5;
                                 m_speed       = 10;
                                 m_accuracy    =  6;
                                 m_iconIndex   =  4;
                                 break;
        }

        setIcon(m_body, m_iconIndex);
    }
    
    sf::String
    MeleeWeapon::getName() const
    {
        sf::String name = "";

        switch (m_type)
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

        name += ((m_identified && m_cursed) ? " - " + Resources::dictionary["item.enchantment.name.cursed"] : "");
        
        return name;
    }

    sf::String
    MeleeWeapon::getDescription() const
    {
        sf::String description = "";

        switch (m_type)
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

        description += "\n" + ((m_identified && m_cursed  ) ? "\n"+Resources::dictionary["item.enchantment.description.cursed"]                                   : "")
                            +                                 "\n"+Resources::dictionary["item.requirement.strength"          ]+" "+std::to_string((int) m_requirement)
                            +                                 "\n"+Resources::dictionary["item.weapon.damage_dealt"           ]+" "+std::to_string((int) m_damageDealt)
                            + ((m_identified && m_level!=0) ? "\n"+Resources::dictionary["item.weapon.level"                  ]+" "+std::to_string((int) m_level) : "");

        return description;
    }

    void
    MeleeWeapon::enhance()
    {
        m_level       ++;
        m_speed       ++;
        m_accuracy    ++;
        m_damageDealt += 5;
        m_requirement -= 3;
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
            readFile <int > (file, m_amount);
            readFile <bool> (file, m_identified);
            readFile <bool> (file, m_equipped);
            readFile <int > (file, m_level);
            readFile <int > (file, type);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        m_type = (Type) type;

        initialize();

        m_speed       += m_level;
        m_accuracy    += m_level;
        m_damageDealt += m_level*5;
        m_requirement -= m_level*3;

        setGridPosition(position);

        return file;
    }

    std::ofstream&
    MeleeWeapon::operator>>(std::ofstream& file)
    {
        file << 3                             << ' '
             << (int) m_body[0].position.x/80 << ' '
             << (int) m_body[0].position.y/80 << ' '
             << m_amount                      << ' '
             << m_identified                  << ' '
             << m_equipped                    << ' '
             << m_level                       << ' '
             << m_type;

        return file;
    }

}

