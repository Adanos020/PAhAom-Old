/**
 * @file src/program/game/entities/entities.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef entities_hpp
#define entities_hpp

namespace rr {
    class Entity {
    public:
        virtual ~Entity() {}

    /// Method drawing the entity's sprite
        virtual void draw       (sf::RenderWindow&) = 0;

    /// Method setting the entity's position
        virtual void setPosition(sf::Vector2f pos ) = 0;
    };
}

#include "item/item.hpp"
#include "chest/chest.hpp"

#endif // entities_hpp

