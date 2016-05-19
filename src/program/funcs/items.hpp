/**
 * @file src/program/game/item/items.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_funcs_h
#define item_funcs_h

#include <iostream>

#include "../game/entities/item/item.hpp"

namespace rr {

/// Returns an instance of the Item class depending on the given ID and amount
    inline Item* getItemFromID(int ID, int amount) {
        switch (ID) {
        /* COIN */
        case   1: return new Coin      (Coin::GOLDEN                , Coin::SMALL         , amount, sf::Vector2i(0, 0));
        case   2: return new Coin      (Coin::SILVER                , Coin::SMALL         , amount, sf::Vector2i(0, 0));
        case   3: return new Coin      (Coin::BRONZE                , Coin::SMALL         , amount, sf::Vector2i(0, 0));
        case   4: return new Coin      (Coin::GOLDEN                , Coin::BIG           , amount, sf::Vector2i(0, 0));
        case   5: return new Coin      (Coin::SILVER                , Coin::BIG           , amount, sf::Vector2i(0, 0));
        case   6: return new Coin      (Coin::BRONZE                , Coin::BIG           , amount, sf::Vector2i(0, 0));

        /* BOOKS */
        case  10: return new Book      (Book::CRAFTING                                    , amount, sf::Vector2i(0, 0));
        case  11: return new Book      (Book::ALCHEMY                                     , amount, sf::Vector2i(0, 0));
        case  12: return new Book      (Book::COLD_WEAPON_MASTERY                         , amount, sf::Vector2i(0, 0));
        case  13: return new Book      (Book::RANGED_WEAPON_MASTERY                       , amount, sf::Vector2i(0, 0));
        case  14: return new Book      (Book::EAGLE_EYE                                   , amount, sf::Vector2i(0, 0));
        case  15: return new Book      (Book::MANA_REGEN                                  , amount, sf::Vector2i(0, 0));
        case  16: return new Book      (Book::HEALTH_REGEN                                , amount, sf::Vector2i(0, 0));
        case  17: return new Book      (Book::FASTER_LEARNING                             , amount, sf::Vector2i(0, 0));
        case  18: return new Book      (Book::SPELLS_BOOK                                 , amount, sf::Vector2i(0, 0));

        /* COLD WEAPON */
        case  20: return new ColdWeapon(ColdWeapon::KNIFE                                 , amount, sf::Vector2i(0, 0));
        case  21: return new ColdWeapon(ColdWeapon::DAGGER                                , amount, sf::Vector2i(0, 0));
        case  22: return new ColdWeapon(ColdWeapon::SWORD                                 , amount, sf::Vector2i(0, 0));
        case  23: return new ColdWeapon(ColdWeapon::SERRATED_SWORD                        , amount, sf::Vector2i(0, 0));
        case  24: return new ColdWeapon(ColdWeapon::AXE                                   , amount, sf::Vector2i(0, 0));
        case  25: return new ColdWeapon(ColdWeapon::DOUBLE_AXE                            , amount, sf::Vector2i(0, 0));
        case  26: return new ColdWeapon(ColdWeapon::HALBERD                               , amount, sf::Vector2i(0, 0));
        case  27: return new ColdWeapon(ColdWeapon::SPEAR                                 , amount, sf::Vector2i(0, 0));
        case  28: return new ColdWeapon(ColdWeapon::LANCE                                 , amount, sf::Vector2i(0, 0));
        case  29: return new ColdWeapon(ColdWeapon::PIQUE                                 , amount, sf::Vector2i(0, 0));
        case  30: return new ColdWeapon(ColdWeapon::LONG_STICK                            , amount, sf::Vector2i(0, 0));
        case  31: return new ColdWeapon(ColdWeapon::CLUB                                  , amount, sf::Vector2i(0, 0));
        case  32: return new ColdWeapon(ColdWeapon::HAMMER                                , amount, sf::Vector2i(0, 0));

        /* POTIONS */
        case 100: return new Potion    (Potion::Effect::HEALING     , Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 110: return new Potion    (Potion::Effect::HEALING     , Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 120: return new Potion    (Potion::Effect::HEALING     , Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        case 101: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 111: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 121: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        case 102: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 112: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 122: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        case 103: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 113: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 123: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        case 104: return new Potion    (Potion::Effect::SPEED       , Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 114: return new Potion    (Potion::Effect::SPEED       , Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 124: return new Potion    (Potion::Effect::SPEED       , Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        case 105: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 115: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 125: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        case 106: return new Potion    (Potion::Effect::POISON      , Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 116: return new Potion    (Potion::Effect::POISON      , Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 126: return new Potion    (Potion::Effect::POISON      , Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        case 107: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 117: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 127: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        case 108: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::SMALL , amount, sf::Vector2i(0, 0));
        case 118: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::MEDIUM, amount, sf::Vector2i(0, 0));
        case 128: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::BIG   , amount, sf::Vector2i(0, 0));

        /*unknown ID?*/
        default : std::cout << "UNKNOWN ITEM ID" << '\n'; return nullptr;
        }

    }

}

#endif // item_funcs_h
