/**
 * @file src/program/game/item/items.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_funcs_h
#define item_funcs_h

#include "../game/item/item.hpp"

namespace rr {

/// Returns an instance of the Item class depending on the given ID and amount
    inline Item* getItemFromID(double ID, int amount) {
        /*unknown ID?*/
        return new Potion(Potion::Effect::HEALING, Potion::Size::BIG, amount, sf::Vector2f(0, 0));
    }

}

#endif // item_funcs_h
