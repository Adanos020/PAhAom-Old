/**
 * @file src/program/game/item/MeleeWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef ITEM_MELEEWEAPON_HPP
#define ITEM_MELEEWEAPON_HPP

#include "../Item.hpp"

namespace rr
{

    class MeleeWeapon : public Weapon
    {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the melee weapon.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type
             {
                 DOUBLE_AXE,
                 HAMMER,
                 HALBERD,
                 AXE,
                 SERRATED_SWORD,
                 LANCE,
                 CLUB,
                 SWORD,
                 SPEAR,
                 PIQUE,
                 LONG_STICK,
                 DAGGER,
                 KNIFE
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             MeleeWeapon(Type = HAMMER, int amount = 1, sf::Vector2i pos = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             MeleeWeapon(MeleeWeapon const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the melee weapon.
             ////////////////////////////////////////////////////////////////////////
             virtual Entity* clone() const override { return new MeleeWeapon(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the melee weapon's type.
             ///
             /// The possible values are:
             /// - HAMMER
             /// - DOUBLE_AXE
             /// - HALBERD
             /// - AXE
             /// - SERRATED_SWORD
             /// - LANCE
             /// - CLUB
             /// - SWORD
             /// - SPEAR
             /// - PIQUE
             /// - LONG_STICK
             /// - DAGGER
             /// - KNIFE
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return m_type; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the melee weapon's name.
             ////////////////////////////////////////////////////////////////////////
             virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the melee weapon's description.
             ////////////////////////////////////////////////////////////////////////
             virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Increases the melee weapon's level and maximum damage dealt by
             /// it and reduces its requirement.
             ////////////////////////////////////////////////////////////////////////
             virtual void enhance() override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Puts an enchantment on the melee weapon.
             ////////////////////////////////////////////////////////////////////////
             virtual void enchant() override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the melee weapon from the file.
             ////////////////////////////////////////////////////////////////////////
             virtual std::ifstream& operator<< (std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the melee weapon to the file.
             ////////////////////////////////////////////////////////////////////////
             virtual std::ofstream& operator>> (std::ofstream&) override;

    private: Type m_type;
    };

}

#endif // ITEM_MELEEWEAPON_HPP
