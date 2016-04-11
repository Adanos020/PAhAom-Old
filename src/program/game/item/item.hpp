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

/// Class for an item
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
    /// A virtual destructor
        virtual ~Item() {}

    /// Method drawing the item's sprite
        virtual void       draw          (sf::RenderWindow&) = 0;

    /// Updates the item's status
        virtual void       update        ()                  = 0;

    /// Method changing the amount
        void               editAmount    (int x)            { amount = x; }

    /// Sets the item's position
        void               setPosition   (sf::Vector2f pos) { body.setPosition(pos); }

    /// Returns the item's ID
        double             getID         ()                 { return ID; }

    /// Returns the amount of this item
        int                getAmount     ()                 { return amount; }

    /// Method telling if the item is disposable
        bool               isDisposable  ()                 { return disposable; }

    /// Method telling if the item is equipable
        bool               isEquipable   ()                 { return equipable; }

    /// Returns the sprite of this item
        sf::Sprite         getBody       ()                 { return body; }

    /// Returns the name of this item
        sf::String         getName       ()                 { return name; }

    /// Returns the description of this item
        sf::String         getDescription()                 { return description; }
    };

    class Discoverable {
    protected:
        bool discovered;
    public:
    /// A virtual destructor
        virtual ~Discoverable() {}

    /// Method reveling the discoverable item's properties
        virtual void reveal () = 0;
    };

}

#include "item_Cash.hpp"
#include "item_ColdWeapon.hpp"
#include "item_Food.hpp"
#include "item_Potion.hpp"
#include "item_RangedWeapon.hpp"
#include "item_Spell.hpp"

#endif
