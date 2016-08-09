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
    private: virtual void           initialize    ()                  override;

    public:  enum Type {
                 HAMMER,
                 DOUBLE_AXE,
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

             ColdWeapon(Type = HAMMER, int amount = 1, sf::Vector2u pos = sf::Vector2u(0, 0));
             ColdWeapon(ColdWeapon const&);

             Type                   getType       () const                  { return type_; }

             virtual Entity*        clone         () const         override { return new ColdWeapon(*this); }

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

#endif // ITEM_COLDWEAPON_HPP
