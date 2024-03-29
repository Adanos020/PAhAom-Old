/**
 * @file src/program/game/item/Rune.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include "../Item.hpp"

namespace rr
{

    class Rune : public Discoverable
    {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the rune.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type
             {
                 HEAL,
                 FIREBOLT,
                 LIGHTNING,
                 ICE_BULLET,
                 TELEPORT,
                 FIRE_RAIN,
                 STORM,
                 ICE_WAVE,
                 TIME_FREEZING,
                 IDENTIFY,
                 UNCURSE,
                 TELEKINESIS
             };

      static bool m_identified[12];

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Rune(Type = HEAL, int am = 1, sf::Vector2i pos = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Rune(Rune const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the rune.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Rune(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the rune's type.
             ///
             /// The possible values are:
             /// - HEAL
             /// - FIREBOLT
             /// - LIGHTNING
             /// - ICE_BULLET
             /// - TELEPORT
             /// - FIRE_RAIN
             /// - STORM
             /// - ICE_WAVE
             /// - TIME_FREEZING
             /// - IDENTIFY
             /// - UNCURSE
             /// - TELEKINESIS
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return m_type; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reveals the rune's properties.
             ////////////////////////////////////////////////////////////////////////
     virtual void reveal() override { m_identified[m_type] = true; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the rune is discovered.
             ////////////////////////////////////////////////////////////////////////
     virtual bool isDiscovered() const override { return m_identified[m_type]; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the rune's name.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the rune's description.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the rune's position relatively to the grid marked out by
             /// the level's tile map.
             ////////////////////////////////////////////////////////////////////////
     virtual void setGridPosition(sf::Vector2i) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the rune's position relatively to the graphics card's
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual void setPosition(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the rune from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the rune to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type m_type;
    };

}
