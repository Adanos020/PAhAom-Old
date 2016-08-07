/**
 * @file src/program/game/entity/Entity.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

namespace rr {

    class Item;

    class Entity : public sf::Drawable {
    public: virtual ~Entity() {}

        /// Virtual constructor: cloning
            virtual Entity*        clone          ()        const     = 0;
        /// Sets the entity's position in relation to the actual coordinate system
            virtual void           setGridPosition(sf::Vector2u pos)  = 0;
        /// Returns the entity's position in relation to the actual coordinate system
            virtual sf::Vector2u   getGridPosition()        const     = 0;
        /// Sets the entity's position in relation to the grid
            virtual void           setPosition    (sf::Vector2f pos)  = 0;
        /// Returns the entity's position in relation to the grid
            virtual sf::Vector2f   getPosition    ()        const     = 0;
        /// Returns the entity's bound box
            virtual sf::FloatRect  getBounds      ()        const     = 0;
        /// Tells if this entity collides with another one
            virtual bool           collides       (Entity*) const     = 0;

            virtual std::ifstream& operator<<     (std::ifstream&)    = 0;
            virtual std::ofstream& operator>>     (std::ofstream&)    = 0;
    
    private: /// Initializes the object
            virtual void           initialize     ()                  = 0; 
    };

}

#endif // ENTITY_HPP
