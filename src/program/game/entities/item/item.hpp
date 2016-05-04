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
        sf::VertexArray _body;
        sf::String      _name;
        sf::String      _description;
        sf::String      _effects;
        sf::String      _requirements;
        bool            _equipable;
        bool            _disposable;
        int             _ID;
        int             _amount;
    public:
    /// A virtual destructor
        virtual ~Item() {}

    /// Updates the item's status
        virtual void       update        () = 0;

    /// Method changing the amount
        void               setAmount     (int x)                     { _amount = x; }

    /// Returns the item's ID
        int                getID         ()                          { return _ID; }

    /// Returns the amount of this item
        int                getAmount     ()                          { return _amount; }

    /// Method telling if the item is disposable
        bool               isDisposable  ()                          { return _disposable; }

    /// Method telling if the item is equipable
        bool               isEquipable   ()                          { return _equipable; }

    /// Returns the sprite of this item
        sf::VertexArray    getBody       ()                          { return _body; }

    /// Returns the name of this item
        sf::String         getName       ()                          { return _name; }

    /// Returns the description of this item
        sf::String         getDescription()                          { return _description; }

        void               setPosition   (sf::Vector2i pos) override { _body[0].position = (sf::Vector2f)pos*80.f;
                                                                       _body[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
                                                                       _body[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
                                                                       _body[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);
                                                                     }

        bool               intersects    (Entity* e) const  override { return (e->getBounds().intersects(getBounds())); }
        sf::FloatRect      getBounds     ()          const  override { return sf::FloatRect(_body[0].position, _body[2].position-_body[0].position); }
    };

    class Discoverable {
    protected:
        bool _discovered;
    public:
    /// A virtual destructor
        virtual ~Discoverable() {}

    /// Method reveling the discoverable item's properties
        virtual void reveal () = 0;
    };

}

#include "item_Book.hpp"
#include "item_Coin.hpp"
#include "item_ColdWeapon.hpp"
#include "item_Food.hpp"
#include "item_Potion.hpp"
#include "item_RangedWeapon.hpp"
#include "item_Spell.hpp"

#endif
