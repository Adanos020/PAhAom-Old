/**
 * @file src/program/game/item/items.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_funcs_h
#define item_funcs_h

#include <iostream>

#include "../game/entities/item/item.hpp"

namespace rr {

/// Returns an instance of the Item class depending on the given ID and amount
    inline Item* getItemFromID(int ID, int amount) {
        switch (ID) {
        /* CASH */
        case 1  : return new Cash  (Cash::BRONZE, amount, sf::Vector2f(0, 0)); break;
        case 2  : return new Cash  (Cash::SILVER, amount, sf::Vector2f(0, 0)); break;
        case 3  : return new Cash  (Cash::GOLDEN, amount, sf::Vector2f(0, 0)); break;
        /* POTIONS */
        case 100: return new Potion(Potion::Effect::HEALING     , Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 110: return new Potion(Potion::Effect::HEALING     , Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 120: return new Potion(Potion::Effect::HEALING     , Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        case 101: return new Potion(Potion::Effect::MAGIC       , Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 111: return new Potion(Potion::Effect::MAGIC       , Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 121: return new Potion(Potion::Effect::MAGIC       , Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        case 102: return new Potion(Potion::Effect::STRENGTH    , Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 112: return new Potion(Potion::Effect::STRENGTH    , Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 122: return new Potion(Potion::Effect::STRENGTH    , Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        case 103: return new Potion(Potion::Effect::DEXTERITY   , Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 113: return new Potion(Potion::Effect::DEXTERITY   , Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 123: return new Potion(Potion::Effect::DEXTERITY   , Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        case 104: return new Potion(Potion::Effect::SPEED       , Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 114: return new Potion(Potion::Effect::SPEED       , Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 124: return new Potion(Potion::Effect::SPEED       , Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        case 105: return new Potion(Potion::Effect::REGENERATION, Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 115: return new Potion(Potion::Effect::REGENERATION, Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 125: return new Potion(Potion::Effect::REGENERATION, Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        case 106: return new Potion(Potion::Effect::POISON      , Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 116: return new Potion(Potion::Effect::POISON      , Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 126: return new Potion(Potion::Effect::POISON      , Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        case 107: return new Potion(Potion::Effect::SLOWNESS    , Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 117: return new Potion(Potion::Effect::SLOWNESS    , Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 127: return new Potion(Potion::Effect::SLOWNESS    , Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        case 108: return new Potion(Potion::Effect::WEAKNESS    , Potion::Size::SMALL , amount, sf::Vector2f(0, 0)); break;
        case 118: return new Potion(Potion::Effect::WEAKNESS    , Potion::Size::MEDIUM, amount, sf::Vector2f(0, 0)); break;
        case 128: return new Potion(Potion::Effect::WEAKNESS    , Potion::Size::BIG   , amount, sf::Vector2f(0, 0)); break;

        /*unknown ID?*/
        default : std::cout << "UNKNOWN ITEM ID" << '\n'; return nullptr;
        }

    }

}

#endif // item_funcs_h
