/**
 * @file src/program/game/item/rangedweapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef item_RangedWeapon_hpp
#define item_RangedWeapon_hpp

#include "item.hpp"

namespace rr {

    class RangedWeapon :public Item {
    private:
    public:
         RangedWeapon();
        ~RangedWeapon();

        virtual void draw      (sf::RenderWindow&) override;
        virtual void editAmount(int)               override;
        virtual void update    ()                  override;
    };

}

#endif // item_RangedWeapon_hpp
