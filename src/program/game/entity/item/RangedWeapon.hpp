/**
 * @file src/program/game/item/RangedWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef ITEM_RANGEDWEAPON_HPP
#define ITEM_RANGEDWEAPON_HPP

#include "../Item.hpp"

namespace rr
{

    class RangedWeapon : public Weapon
    {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the ranged weapon.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type
             {
                 BOW,
                 CROSSBOW,
                 SLINGSHOT,
                 BELLOWS
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             RangedWeapon(Type = BOW, int amount = 1, sf::Vector2i position = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             RangedWeapon(RangedWeapon const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the ranged weapon.
             ////////////////////////////////////////////////////////////////////////
             virtual Entity* clone() const override { return new RangedWeapon(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the ranged weapon's type.
             ///
             /// The possible values are:
             /// - BOW
             /// - CROSSBOW
             /// - SLINGSHOT
             /// - BELLOWS
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return m_type; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the ranged weapon's name.
             ////////////////////////////////////////////////////////////////////////
             virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the ranged weapon's description.
             ////////////////////////////////////////////////////////////////////////
             virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Increases the ranged weapon's level and maximum damage dealt
             /// by it and reduces its requirement.
             ////////////////////////////////////////////////////////////////////////
             virtual void enhance() override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Puts an enchantment on the ranged weapon.
             ////////////////////////////////////////////////////////////////////////
             virtual void enchant() override;

             virtual std::ifstream& operator<<(std::ifstream&) override;
             virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type m_type;
    };

}

#endif // ITEM_RANGEDWEAPON_HPP
