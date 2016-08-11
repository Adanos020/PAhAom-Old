/**
 * @file src/program/game/item/Rune.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_RUNE_HPP
#define ITEM_RUNE_HPP

#include "Item.hpp"

namespace rr {

    class Rune : public Discoverable {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the rune.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type {
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

      static bool identified_[12];

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
             Type getType() const { return type_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reveals the rune's properties.
             ////////////////////////////////////////////////////////////////////////
     virtual void reveal() override { identified_[type_] = true; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the rune is discovered.
             ////////////////////////////////////////////////////////////////////////
     virtual bool isDiscovered() const override { return identified_[type_]; }

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
             void setGridPosition(sf::Vector2i) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the rune's position relatively to the graphics card's
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
             void setPosition(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the rune from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the rune to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type type_;
    };

}

#endif // ITEM_RUNE_HPP
