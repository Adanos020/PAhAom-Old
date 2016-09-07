/**
 * @file src/program/game/item/RangedWeapon.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "RangedWeapon.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"

namespace rr
{

    RangedWeapon::RangedWeapon(Type type, int amount, sf::Vector2i position) :
      m_type(type)
    {
        m_level      = 0;
        m_identified = false;
        m_amount     = amount;

        initialize();
        setGridPosition(position);
    }

    RangedWeapon::RangedWeapon(RangedWeapon const& copy) :
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
    RangedWeapon::initialize()
    {
        m_disposable = false;
        m_stackable  = false;
        m_cursed     = chance(1, 4);
        m_ID         = m_type + 23;
        m_iconIndex  = m_type + 52;

        switch (m_type)
        {
            case BOW      : m_damageDealt = 40;
                            m_requirement = 25;
                            m_speed       =  7;
                            m_accuracy    =  9;
                            break;

            case CROSSBOW : m_damageDealt = 50;
                            m_requirement = 40;
                            m_speed       =  6;
                            m_accuracy    =  8;
                            break;

            case SLINGSHOT: m_damageDealt = 30;
                            m_requirement = 15;
                            m_speed       =  8;
                            m_accuracy    =  5;
                            break;

            case BELLOWS  : m_damageDealt = 35;
                            m_requirement = 17;
                            m_speed       =  7;
                            m_accuracy    =  7;
                            break;
        }

        setIcon(m_body, m_iconIndex);
    }

    sf::String
    RangedWeapon::getName() const
    {
        switch (m_type)
        {
            case BOW      : return Resources::dictionary["item.ranged_weapon.name.bow"      ];
            case CROSSBOW : return Resources::dictionary["item.ranged_weapon.name.crossbow" ];
            case SLINGSHOT: return Resources::dictionary["item.ranged_weapon.name.slingshot"];
            case BELLOWS  : return Resources::dictionary["item.ranged_weapon.name.bellows"  ];
        }

        return "";
    }

    sf::String
    RangedWeapon::getDescription() const
    {
        sf::String description = "";
        switch (m_type)
        {
            case BOW      : description += Resources::dictionary["item.ranged_weapon.description.bow"      ] + "\n\n"
                                         + Resources::dictionary["item.requirement.item"                   ] + " "
                                         + Resources::dictionary["item.ammunition.name.arrow"              ];
                            break;

            case CROSSBOW : description += Resources::dictionary["item.ranged_weapon.description.crossbow" ] + "\n\n"
                                         + Resources::dictionary["item.requirement.item"                   ] + " "
                                         + Resources::dictionary["item.ammunition.name.bolt"               ];
                            break;

            case SLINGSHOT: description += Resources::dictionary["item.ranged_weapon.description.slingshot"] + "\n\n"
                                         + Resources::dictionary["item.requirement.item"                   ] + " "
                                         + Resources::dictionary["item.ammunition.name.rocks"              ];
                            break;

            case BELLOWS  : description += Resources::dictionary["item.ranged_weapon.description.bellows"  ] + "\n\n"
                                         + Resources::dictionary["item.requirement.item"                   ] + " "
                                         + Resources::dictionary["item.ammunition.name.dart"               ];
                            break;
        }

        description += "\n" + ((m_identified && m_cursed  ) ? "\n"+Resources::dictionary["item.enchantment.description.cursed"]                                   : "")
                            +                                 "\n"+Resources::dictionary["item.requirement.dexterity"         ]+" "+std::to_string((int) m_requirement)
                            +                                 "\n"+Resources::dictionary["item.weapon.damage_dealt"           ]+" "+std::to_string((int) m_damageDealt)
                            + ((m_identified && m_level!=0) ? "\n"+Resources::dictionary["item.weapon.level"                  ]+" "+std::to_string((int) m_level) : "");

        return description;
    }

    void
    RangedWeapon::enhance()
    {
        m_level       ++;
        m_speed       ++;
        m_accuracy    ++;
        m_damageDealt += 5;
        m_requirement -= 3;
    }

    void
    RangedWeapon::enchant()
    {

    }

    std::ifstream&
    RangedWeapon::operator<<(std::ifstream& file)
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
    RangedWeapon::operator>>(std::ofstream& file)
    {
        file << 6                             << ' '
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
