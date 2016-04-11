/**
 * @file src/program/game/item/item.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_h
#define item_h

#include <SFML/Graphics.hpp>

namespace rr {

    class Item {
    protected:
        sf::FloatRect   boundBox;
        sf::Sprite      body;
        sf::String      name;
        sf::String      description;
        sf::String      effects;
        sf::String      requirements;
        bool            equipable;
        bool            disposable;
        double          ID;
        int             amount;
    public:
        virtual ~Item() {}

        virtual void       draw          (sf::RenderWindow&) = 0;
        virtual void       editAmount    (int)               = 0;
        virtual void       update        ()                  = 0;

        double             getID         () { return ID; }
        int                getAmount     () { return amount; }
        bool               isDisposable  () { return disposable; }
        bool               isEquipable   () { return equipable; }
        sf::Sprite         getBody       () { return body; }
        sf::String         getName       () { return name; }
        sf::String         getDescription() { return description; }
    };

    class Discoverable {
    protected:
        bool discovered;
    public:
        virtual ~Discoverable() {}
        virtual void reveal  () = 0;
    };

}

#include "item_Cash.hpp"
#include "item_ColdWeapon.hpp"
#include "item_Food.hpp"
#include "item_Potion.hpp"
#include "item_RangedWeapon.hpp"
#include "item_Spell.hpp"

#endif
