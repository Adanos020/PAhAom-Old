/**
 * @file src/program/game/item/item_RangedWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_RangedWeapon_hpp
#define item_RangedWeapon_hpp

#include "item.hpp"

namespace rr {

    class RangedWeapon : public Item {
    private:
    public:
         RangedWeapon();
         RangedWeapon(RangedWeapon const&);
        ~RangedWeapon();
/*
        virtual Entity* clone ()            const override { return new RangedWeapon(*this); }
        virtual Entity* create()            const override { return new RangedWeapon(); }
*/
        virtual void    draw  (sf::RenderWindow&) override;
    };

}

#endif // item_RangedWeapon_hpp
