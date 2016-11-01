/**
 * @file src/program/game/Entity.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

namespace rr
{

    class Item;

    class Entity : public sf::Drawable 
    {
    public:  enum Species
             {
                 NONE,
                 CHEST,
                 DOOR,
                 ITEM,
                 N_P_C,
                 PLAYER,
                 STAIRS
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Virtual destructor.
             ////////////////////////////////////////////////////////////////////////
     virtual ~Entity() {}

             ////////////////////////////////////////////////////////////////////////
             /// \brief Virtual constructor: cloning
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the entity's position in relation to the actual
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual void setGridPosition(sf::Vector2i pos) = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the entity's position in relation to the actual
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2i getGridPosition() const = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the entity's position in relation to the grid.
             ////////////////////////////////////////////////////////////////////////
     virtual void setPosition(sf::Vector2f pos) = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the entity's position in relation to the grid.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2f getPosition() const = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the entity's bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::FloatRect getBounds() const = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if this entity collides with another one.
             ////////////////////////////////////////////////////////////////////////
     virtual bool collides(Entity*) const = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the entity from file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<< (std::ifstream&) = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Writes the entity to file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>> (std::ofstream&) = 0;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the species of the entity.
             ////////////////////////////////////////////////////////////////////////
     virtual Species getSpecies() const = 0;

    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the object.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() = 0; 
    };

}

#endif // ENTITY_HPP
