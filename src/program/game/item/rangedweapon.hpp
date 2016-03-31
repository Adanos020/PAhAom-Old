/**
 * @file src/program/game/item/rangedweapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "item.h"

namespace rr {

    class RangedWeapon :public Item {
      private:
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int)         override;
        virtual void update()                override;
    };

}
