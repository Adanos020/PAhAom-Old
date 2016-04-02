/**
 * @file src/program/game/item/cash.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef item_Cash_hpp
#define item_Cash_hpp

#include "item.h"

namespace rr {

    //class Item;

    class Cash :public Item {
      private:
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int)         override;
        virtual void update()                override;
    };

}

#endif // item_Cash_hpp
