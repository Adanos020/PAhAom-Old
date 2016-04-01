/**
 * @file src/program/game/item/spell.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef item_Spell_hpp
#define item_Spell_hpp

#include "item.h"

namespace rr {

    class Spell :public Item {
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int)         override;
        virtual void update()                override;
    };

}

#endif // item_Spell_hpp
