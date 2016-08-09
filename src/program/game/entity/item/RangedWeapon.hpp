/**
 * @file src/program/game/item/RangedWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_RANGEDWEAPON_HPP
#define ITEM_RANGEDWEAPON_HPP

#include "Item.hpp"

namespace rr {

    class RangedWeapon : public Weapon {
    private: virtual void           initialize    ()               override;

    public:  enum Type {
                 BOW,
                 CROSSBOW,
                 SLINGSHOT
             };

             RangedWeapon(Type = BOW, int amount = 1, sf::Vector2u position = sf::Vector2u(0, 0));
             RangedWeapon(RangedWeapon const&);

             Type                   getType       () const                  { return type_; }

             virtual Entity*        clone         () const         override { return new RangedWeapon(*this); }

             virtual sf::String     getName       () const         override;
             virtual sf::String     getDescription() const         override;

             virtual void           equip         (bool b)         override { equipped_ = b; }
             virtual bool           isEquipped    () const         override { return equipped_; }

             virtual void           reveal        ()               override { identified_ = true; }

             virtual void           enhance       ()               override;
             virtual void           enchant       ()               override;

             virtual std::ifstream& operator<<    (std::ifstream&) override;
             virtual std::ofstream& operator>>    (std::ofstream&) override;

    private: Type type_;
    };

}

#endif // ITEM_RANGEDWEAPON_HPP
