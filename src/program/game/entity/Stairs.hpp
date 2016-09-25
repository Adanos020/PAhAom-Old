/**
 * @file src/program/game/entity/Stairs.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef ENTITY_STAIRS_HPP
#define ENTITY_STAIRS_HPP

#include "../Entity.hpp"

namespace rr
{

    class Stairs : public Entity
    {
    private: sf::Sprite m_body;
             bool       m_upwards;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the stairs.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the starirs' body and texture on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Stairs(bool upwards = true);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Stairs(Stairs const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the stairs.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Stairs(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the stairs are upwards.
             ////////////////////////////////////////////////////////////////////////
             bool isUpwards() const { return m_upwards; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the stairs' position relatively to the grid marked out
             /// by the level's tile map.
             ////////////////////////////////////////////////////////////////////////
     virtual void setGridPosition(sf::Vector2i pos) override { m_body.setPosition((sf::Vector2f) pos*80.f); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the stairs' position relatively to the grid marked
             /// out by the level's tile map.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2i getGridPosition() const override { return (sf::Vector2i) m_body.getPosition()/80; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the stairs' position relatively to the graphics card's
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual void setPosition(sf::Vector2f pos) override { m_body.setPosition(pos); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the stairs' position relatively to the graphics
             /// card's coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2f getPosition() const override { return m_body.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if another entity's bound box intersects with the
             /// stairs' bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual bool collides(Entity* e) const override { return e->getBounds().intersects(getBounds()); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the stairs' bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::FloatRect getBounds() const override { return m_body.getGlobalBounds(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the stairs from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the stairs to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;
    };

}

#endif // ENTITY_STAIRS_HPP
