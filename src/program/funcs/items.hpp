/**
 * @file src/program/game/item/items.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FUNCS_ITEMS_HPP
#define FUNCS_ITEMS_HPP

#include <cstdio>

#include "classes.hpp"
#include "random.hpp"

#include "../game/entity/item/Item.hpp"
#include "../game/entity/item/ALL.hpp"

namespace rr {

/// Returns an instance of the Item class depending on the given ID and amount
    inline Item* getItemFromID(int ID, int amount) {
        switch (ID) {
            /* COIN */
            case   1: return new Coin        (Coin::GOLDEN                , Coin::SMALL         , amount);
            case   2: return new Coin        (Coin::SILVER                , Coin::SMALL         , amount);
            case   3: return new Coin        (Coin::BRONZE                , Coin::SMALL         , amount);
            case   4: return new Coin        (Coin::GOLDEN                , Coin::BIG           , amount);
            case   5: return new Coin        (Coin::SILVER                , Coin::BIG           , amount);
            case   6: return new Coin        (Coin::BRONZE                , Coin::BIG           , amount);

            /* COLD WEAPON */
            case  10: return new ColdWeapon  (ColdWeapon::HAMMER                                , amount);
            case  11: return new ColdWeapon  (ColdWeapon::DOUBLE_AXE                            , amount);
            case  12: return new ColdWeapon  (ColdWeapon::HALBERD                               , amount);
            case  13: return new ColdWeapon  (ColdWeapon::AXE                                   , amount);
            case  14: return new ColdWeapon  (ColdWeapon::SERRATED_SWORD                        , amount);
            case  15: return new ColdWeapon  (ColdWeapon::LANCE                                 , amount);
            case  16: return new ColdWeapon  (ColdWeapon::CLUB                                  , amount);
            case  17: return new ColdWeapon  (ColdWeapon::SWORD                                 , amount);
            case  18: return new ColdWeapon  (ColdWeapon::SPEAR                                 , amount);
            case  19: return new ColdWeapon  (ColdWeapon::PIQUE                                 , amount);
            case  20: return new ColdWeapon  (ColdWeapon::LONG_STICK                            , amount);
            case  21: return new ColdWeapon  (ColdWeapon::DAGGER                                , amount);
            case  22: return new ColdWeapon  (ColdWeapon::KNIFE                                 , amount);

            /* RANGED WEAPON */
            case  23: return new RangedWeapon(RangedWeapon::BOW                                 , amount);
            case  24: return new RangedWeapon(RangedWeapon::CROSSBOW                            , amount);
            case  25: return new RangedWeapon(RangedWeapon::SLINGSHOT                           , amount);

            /* AMMUNITION */
            case  26: // arrow
            case  27: // bolt
            case  28: // rocks
            case  29: // shuriken

            /* BOOKS */
            case  30: return new Book        (Book::CRAFTING                                    , amount);
            case  31: return new Book        (Book::ALCHEMY                                     , amount);
            case  32: return new Book        (Book::COLD_WEAPON_MASTERY                         , amount);
            case  33: return new Book        (Book::RANGED_WEAPON_MASTERY                       , amount);
            case  34: return new Book        (Book::EAGLE_EYE                                   , amount);
            case  35: return new Book        (Book::MANA_REGEN                                  , amount);
            case  36: return new Book        (Book::HEALTH_REGEN                                , amount);
            case  37: return new Book        (Book::FASTER_LEARNING                             , amount);
            case  38: return new Book        (Book::SPELLS_BOOK                                 , amount);

            /* RUNES */
            case  39: return new Rune        (Rune::HEAL                                        , amount);
            case  40: return new Rune        (Rune::FIREBOLT                                    , amount);
            case  41: return new Rune        (Rune::LIGHTNING                                   , amount);
            case  42: return new Rune        (Rune::ICE_BULLET                                  , amount);
            case  43: return new Rune        (Rune::TELEPORT                                    , amount);
            case  44: return new Rune        (Rune::FIRE_RAIN                                   , amount);
            case  45: return new Rune        (Rune::STORM                                       , amount);
            case  46: return new Rune        (Rune::ICE_WAVE                                    , amount);
            case  47: return new Rune        (Rune::TIME_FREEZING                               , amount);
            case  48: return new Rune        (Rune::IDENTIFY                                    , amount);
            case  49: return new Rune        (Rune::UNCURSE                                     , amount);
            case  50: return new Rune        (Rune::TELEKINESIS                                 , amount);

            /* FOOD */
            case  51: return new Food        (Food::MEAT                                        , amount);
            case  52: return new Food        (Food::SANDVICH                                    , amount);
            case  53: return new Food        (Food::APPLE                                       , amount);
            case  54: return new Food        (Food::BEER                                        , amount);
            case  55: return new Food        (Food::HOT_DOG                                     , amount);
            case  56: return new Food        (Food::HAMBURGER                                   , amount);
            case  57: return new Food        (Food::BAGUETTE                                    , amount);

            /* POTIONS */
            case 100: return new Potion      (Potion::HEALING             , Potion::BIG         , amount);
            case 101: return new Potion      (Potion::HEALING             , Potion::MEDIUM      , amount);
            case 102: return new Potion      (Potion::HEALING             , Potion::SMALL       , amount);

            case 110: return new Potion      (Potion::MAGIC               , Potion::BIG         , amount);
            case 111: return new Potion      (Potion::MAGIC               , Potion::MEDIUM      , amount);
            case 112: return new Potion      (Potion::MAGIC               , Potion::SMALL       , amount);

            case 120: return new Potion      (Potion::STRENGTH            , Potion::BIG         , amount);
            case 121: return new Potion      (Potion::STRENGTH            , Potion::MEDIUM      , amount);
            case 122: return new Potion      (Potion::STRENGTH            , Potion::SMALL       , amount);

            case 130: return new Potion      (Potion::DEXTERITY           , Potion::BIG         , amount);
            case 131: return new Potion      (Potion::DEXTERITY           , Potion::MEDIUM      , amount);
            case 132: return new Potion      (Potion::DEXTERITY           , Potion::SMALL       , amount);

            case 140: return new Potion      (Potion::SPEED               , Potion::BIG         , amount);
            case 141: return new Potion      (Potion::SPEED               , Potion::MEDIUM      , amount);
            case 142: return new Potion      (Potion::SPEED               , Potion::SMALL       , amount);

            case 150: return new Potion      (Potion::REGENERATION        , Potion::BIG         , amount);
            case 151: return new Potion      (Potion::REGENERATION        , Potion::MEDIUM      , amount);
            case 152: return new Potion      (Potion::REGENERATION        , Potion::SMALL       , amount);

            case 160: return new Potion      (Potion::POISON              , Potion::BIG         , amount);
            case 161: return new Potion      (Potion::POISON              , Potion::MEDIUM      , amount);
            case 162: return new Potion      (Potion::POISON              , Potion::SMALL       , amount);

            case 170: return new Potion      (Potion::SLOWNESS            , Potion::BIG         , amount);
            case 171: return new Potion      (Potion::SLOWNESS            , Potion::MEDIUM      , amount);
            case 172: return new Potion      (Potion::SLOWNESS            , Potion::SMALL       , amount);

            case 180: return new Potion      (Potion::WEAKNESS            , Potion::BIG         , amount);
            case 181: return new Potion      (Potion::WEAKNESS            , Potion::MEDIUM      , amount);
            case 182: return new Potion      (Potion::WEAKNESS            , Potion::SMALL       , amount);

            /*unknown ID?*/
            default : printf("UNKNOWN ITEM ID: %d\n", ID); return nullptr;
        }

    }

    inline Item* getRandomItem(int amount = 1) {
        int IDs[] = {
              1,   2,   3,   4,   5,   6,                                    // COINS
             10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22, // COLD WEAPON
             30,  31,  32,  33,  34,  35,  36,  37,  38,                     // BOOKS
             39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,      // RUNES
             51,  52,  53,  54,  55,  56,  57,                               // FOOD
            100, 101, 102, 110, 111, 112, 120, 121, 122, 130, 131, 132,      // POTIONS
            140, 141, 142, 150, 151, 152, 160, 161, 162, 170, 171, 172,
            180, 181, 182 
        };
        return getItemFromID(elementOf(IDs, sizeof(IDs)/sizeof(*IDs)), amount);
    }

    inline Item* getRandomItemBalanced() {
        auto item = getRandomItem();

        if (instanceof<Coin, Item>(item)) {
            auto coin = (Coin*) item;

            if (coin->getSize() == Coin::SMALL) {
                switch (coin->getType()) {
                    case Coin::BRONZE: coin->setAmount(rand() % 50 + 1); break;
                    case Coin::SILVER: coin->setAmount(rand() % 10 + 1); break;
                    case Coin::GOLDEN: coin->setAmount(rand() %  3 + 1); break;
                }
            }
            else if (coin->getSize() == Coin::BIG) {
                switch (coin->getType()) {
                    case Coin::BRONZE: coin->setAmount(rand() % 10 + 1); break;
                    case Coin::SILVER: coin->setAmount(rand() %  2 + 1); break;
                    case Coin::GOLDEN: if (chance(0.75)) {
                                           *coin = Coin(chance(1, 3) ? Coin::BRONZE : Coin::SILVER,
                                                        coin->getSize(),
                                                        coin->getAmount());
                                       } else coin->setAmount(1);        break;
                }
            }
        }
        else if (instanceof<Potion, Item>(item)) {
            auto potion = (Potion*) item;

            if (potion->getType() == Potion::STRENGTH || Potion::DEXTERITY) {
                int eff = rand() % 6;
                switch (eff) {
                    case 0: potion = new Potion(Potion::HEALING     , potion->getSize()); break;
                    case 1: potion = new Potion(Potion::MAGIC       , potion->getSize()); break;
                    case 2: potion = new Potion(Potion::SPEED       , potion->getSize()); break;
                    case 3: potion = new Potion(Potion::REGENERATION, potion->getSize()); break;
                    case 4: potion = new Potion(Potion::POISON      , potion->getSize()); break;
                    case 5: potion = new Potion(Potion::SLOWNESS    , potion->getSize()); break;
                }
            }
        }

        return item;
    }

}

#endif // FUNCS_ITEMS_HPP
