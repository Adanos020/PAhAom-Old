/**
 * @file src/program/game/item/ColdWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_COLDWEAPON_HPP
#define ITEM_COLDWEAPON_HPP

#include "Item.hpp"

namespace rr {

    class ColdWeapon : public Weapon {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the cold weapon.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type {
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
             ColdWeapon(Type = HAMMER, int amount = 1, sf::Vector2i pos = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             ColdWeapon(ColdWeapon const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the cold weapon.
             ////////////////////////////////////////////////////////////////////////
             virtual Entity*        clone         () const         override { return new ColdWeapon(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the cold weapon's type.
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
             Type getType() const { return type_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the cold weapon's name.
             ////////////////////////////////////////////////////////////////////////
             virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the cold weapon's description.
             ////////////////////////////////////////////////////////////////////////
             virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Increases the cold weapon's level and maximum damage dealt by
             /// it and reduces its requirement.
             ////////////////////////////////////////////////////////////////////////
             virtual void enhance() override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Puts an enchantment on the cold weapon.
             ////////////////////////////////////////////////////////////////////////
             virtual void enchant() override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the cold weapon from the file.
             ////////////////////////////////////////////////////////////////////////
             virtual std::ifstream& operator<< (std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the cold weapon to the file.
             ////////////////////////////////////////////////////////////////////////
             virtual std::ofstream& operator>> (std::ofstream&) override;

    private: Type type_;
    };

}

#endif // ITEM_COLDWEAPON_HPP
