/**
 * @file src/program/game/item/RangedWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_RANGEDWEAPON_HPP
#define ITEM_RANGEDWEAPON_HPP

#include "Item.hpp"

namespace rr {

    class RangedWeapon : public Equipable {
    public: RangedWeapon();
            RangedWeapon(RangedWeapon const&);
/*
            virtual Entity*        clone     ()            const override { return new RangedWeapon(*this); }
*/    
            virtual sf::String     getName        ()            const override;
            virtual sf::String     getDescription ()            const override;
    
            virtual std::ifstream& operator<<(std::ifstream&)    override;
            virtual std::ofstream& operator>>(std::ofstream&)    override;
    };

}

#endif // ITEM_RANGEDWEAPON_HPP
