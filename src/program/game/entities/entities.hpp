/**
 * @file src/program/game/entities/entities.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef entities_hpp
#define entities_hpp

#include <SFML/Graphics.hpp>

namespace rr {

    class Item;

    class Entity {
    public:
        virtual ~Entity() {}

    /// Draws the entity's sprite
        virtual void          draw           (sf::RenderWindow&) = 0;

    /// Sets the entity's position in relation to the grid
        virtual void          setPosition    (sf::Vector2i pos)  = 0;

    /// Sets the entity's position in relation to the actual coordinate system
        virtual void          setRealPosition(sf::Vector2f pos)  = 0;

    /// Tells if this entity collides with another one
        virtual bool          intersects     (Entity*) const     = 0;

    /// Returns the entity's bound box
        virtual sf::FloatRect getBounds      ()        const     = 0;

    /// Returns the entity's position in relation to the grid
        virtual sf::Vector2i  getPosition    ()        const     = 0;

    /// Returns the entity's position in relation to the actual coordinate system
        virtual sf::Vector2f  getRealPosition()        const     = 0;
    };

}

#include "chest/chest.hpp"
#include "door/door.hpp"
#include "item/item.hpp"
#include "player/player.hpp"
#include "mask/mask.hpp"
#include "stairs/stairs.hpp"

#endif // entities_hpp

