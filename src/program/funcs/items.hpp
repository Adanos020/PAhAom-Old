/**
 * @file src/program/game/item/items.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_funcs_hpp
#define item_funcs_hpp

#include <cstdio>

#include "../game/entities/item/item.hpp"

namespace rr {

/// Returns an instance of the Item class depending on the given ID and amount
    inline Item* getItemFromID(int ID, int amount) {
        switch (ID) {
            /* COIN */
            case   1: return new Coin      (Coin::GOLDEN                , Coin::SMALL         , amount);
            case   2: return new Coin      (Coin::SILVER                , Coin::SMALL         , amount);
            case   3: return new Coin      (Coin::BRONZE                , Coin::SMALL         , amount);
            case   4: return new Coin      (Coin::GOLDEN                , Coin::BIG           , amount);
            case   5: return new Coin      (Coin::SILVER                , Coin::BIG           , amount);
            case   6: return new Coin      (Coin::BRONZE                , Coin::BIG           , amount);

            /* COLD WEAPON */
            case  10: return new ColdWeapon(ColdWeapon::HAMMER                                , amount);
            case  11: return new ColdWeapon(ColdWeapon::DOUBLE_AXE                            , amount);
            case  12: return new ColdWeapon(ColdWeapon::HALBERD                               , amount);
            case  13: return new ColdWeapon(ColdWeapon::AXE                                   , amount);
            case  14: return new ColdWeapon(ColdWeapon::SERRATED_SWORD                        , amount);
            case  15: return new ColdWeapon(ColdWeapon::LANCE                                 , amount);
            case  16: return new ColdWeapon(ColdWeapon::CLUB                                  , amount);
            case  17: return new ColdWeapon(ColdWeapon::SWORD                                 , amount);
            case  18: return new ColdWeapon(ColdWeapon::SPEAR                                 , amount);
            case  19: return new ColdWeapon(ColdWeapon::PIQUE                                 , amount);
            case  20: return new ColdWeapon(ColdWeapon::LONG_STICK                            , amount);
            case  21: return new ColdWeapon(ColdWeapon::DAGGER                                , amount);
            case  22: return new ColdWeapon(ColdWeapon::KNIFE                                 , amount);

            /* BOOKS */
            case  30: return new Book      (Book::CRAFTING                                    , amount);
            case  31: return new Book      (Book::ALCHEMY                                     , amount);
            case  32: return new Book      (Book::COLD_WEAPON_MASTERY                         , amount);
            case  33: return new Book      (Book::RANGED_WEAPON_MASTERY                       , amount);
            case  34: return new Book      (Book::EAGLE_EYE                                   , amount);
            case  35: return new Book      (Book::MANA_REGEN                                  , amount);
            case  36: return new Book      (Book::HEALTH_REGEN                                , amount);
            case  37: return new Book      (Book::FASTER_LEARNING                             , amount);
            case  38: return new Book      (Book::SPELLS_BOOK                                 , amount);

            /* RUNES */
            case  39: return new Rune      (Rune::HEAL                                        , amount);
            case  40: return new Rune      (Rune::FIREBOLT                                    , amount);
            case  41: return new Rune      (Rune::LIGHTNING                                   , amount);
            case  42: return new Rune      (Rune::ICE_BULLET                                  , amount);
            case  43: return new Rune      (Rune::TELEPORT                                    , amount);
            case  44: return new Rune      (Rune::FIRE_RAIN                                   , amount);
            case  45: return new Rune      (Rune::STORM                                       , amount);
            case  46: return new Rune      (Rune::ICE_WAVE                                    , amount);
            case  47: return new Rune      (Rune::TIME_FREEZING                               , amount);
            case  48: return new Rune      (Rune::IDENTIFY                                    , amount);
            case  49: return new Rune      (Rune::UNCURSE                                     , amount);
            case  50: return new Rune      (Rune::TELEKINESIS                                 , amount);

            /* POTIONS */
            case 100: return new Potion    (Potion::Effect::HEALING     , Potion::Size::BIG   , amount);
            case 101: return new Potion    (Potion::Effect::HEALING     , Potion::Size::MEDIUM, amount);
            case 102: return new Potion    (Potion::Effect::HEALING     , Potion::Size::SMALL , amount);

            case 110: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::BIG   , amount);
            case 111: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::MEDIUM, amount);
            case 112: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::SMALL , amount);

            case 120: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::BIG   , amount);
            case 121: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::MEDIUM, amount);
            case 122: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::SMALL , amount);

            case 130: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::BIG   , amount);
            case 131: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::MEDIUM, amount);
            case 132: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::SMALL , amount);

            case 140: return new Potion    (Potion::Effect::SPEED       , Potion::Size::BIG   , amount);
            case 141: return new Potion    (Potion::Effect::SPEED       , Potion::Size::MEDIUM, amount);
            case 142: return new Potion    (Potion::Effect::SPEED       , Potion::Size::SMALL , amount);

            case 150: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::BIG   , amount);
            case 151: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::MEDIUM, amount);
            case 152: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::SMALL , amount);

            case 160: return new Potion    (Potion::Effect::POISON      , Potion::Size::BIG   , amount);
            case 161: return new Potion    (Potion::Effect::POISON      , Potion::Size::MEDIUM, amount);
            case 162: return new Potion    (Potion::Effect::POISON      , Potion::Size::SMALL , amount);

            case 170: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::BIG   , amount);
            case 171: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::MEDIUM, amount);
            case 172: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::SMALL , amount);

            case 180: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::BIG   , amount);
            case 181: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::MEDIUM, amount);
            case 182: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::SMALL , amount);

            /*unknown ID?*/
            default : printf("UNKNOWN ITEM ID: %d\n", ID); return nullptr;
        }

    }

    inline Item* getRandomItem(int amount = 1) {
        int IDs[] {
              1,   2,   3,   4,   5,   6,                                    // COINS
             10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22, // COLD WEAPON
             30,  31,  32,  33,  34,  35,  36,  37,  38,                     // BOOKS
             39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,      // RUNES
            100, 101, 102, 110, 111, 112, 120, 121, 122, 130, 131, 132,      // POTIONS
            140, 141, 142, 150, 151, 152, 160, 161, 162, 170, 171, 172,
            180, 181, 182 
        };
        return getItemFromID(IDs[rand()%(sizeof(IDs)/sizeof(*IDs))], amount);
    }

}

#endif // item_funcs_hpp
