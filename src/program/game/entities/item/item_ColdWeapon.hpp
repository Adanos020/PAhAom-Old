/**
 * @file src/program/game/item/item_ColdWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_ColdWeapon_hpp
#define item_ColdWeapon_hpp

#include "item.hpp"

namespace rr {

    class ColdWeapon : public Item {
    private:
    public:
         ColdWeapon();
        ~ColdWeapon();

        virtual void draw (sf::RenderWindow&) override;
    };

}

#endif // item_ColdWeapon_hpp

