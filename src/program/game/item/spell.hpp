/**
 * @file src/program/game/item/spell.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "item.h"

namespace {

    class Spell :public Item {
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int)         override;
        virtual void update()                override;
    };

}
