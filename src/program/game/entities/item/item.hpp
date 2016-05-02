/**
 * @file src/program/game/entities/item/item.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_h
#define item_h

#include <SFML/Graphics.hpp>

#include "../entities.hpp"

namespace rr {

/// Class for an item
    class Item : public Entity {
    protected:
        sf::FloatRect   boundBox;
        sf::VertexArray body;
        sf::String      name;
        sf::String      description;
        sf::String      effects;
        sf::String      requirements;
        bool            equipable;
        bool            disposable;
        int             ID;
        int             amount;
    public:
    /// A virtual destructor
        virtual ~Item() {}

    /// Updates the item's status
        virtual void       update        ()                  = 0;

    /// Method changing the amount
        void               editAmount    (int x)                     { amount = x; }

    /// Returns the item's ID
        int                getID         ()                          { return ID; }

    /// Returns the amount of this item
        int                getAmount     ()                          { return amount; }

    /// Method telling if the item is disposable
        bool               isDisposable  ()                          { return disposable; }

    /// Method telling if the item is equipable
        bool               isEquipable   ()                          { return equipable; }

    /// Returns the sprite of this item
        sf::VertexArray    getBody       ()                          { return body; }

    /// Returns the name of this item
        sf::String         getName       ()                          { return name; }

    /// Returns the description of this item
        sf::String         getDescription()                          { return description; }

        void               setPosition   (sf::Vector2f pos) override { body[0].position = pos;
                                                                       body[1].position = sf::Vector2f(pos.x+80, pos.y);
                                                                       body[2].position = sf::Vector2f(pos.x+80, pos.y+80);
                                                                       body[3].position = sf::Vector2f(pos.x   , pos.y+80);
                                                                     }

        bool               intersects    (Entity* e) const  override { return (e->getBounds().intersects(this->getBounds())); }
        sf::FloatRect      getBounds     ()          const  override { return sf::FloatRect(body[0].position, body[2].position-body[0].position); }
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

#include "item_Book.hpp"
#include "item_Cash.hpp"
#include "item_ColdWeapon.hpp"
#include "item_Food.hpp"
#include "item_Potion.hpp"
#include "item_RangedWeapon.hpp"
#include "item_Spell.hpp"

#endif
