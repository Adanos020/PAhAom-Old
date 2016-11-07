/**
 * @file src/program/game/item/Potion.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include "../Item.hpp"

namespace rr
{

    class Potion : public Discoverable
    {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the potion.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;
    
    public:  enum Type
             {
                 HEALING,
                 MAGIC,
                 STRENGTH,
                 DEXTERITY,
                 SPEED,
                 REGENERATION,
                 POISON,
                 SLOWNESS,
                 WEAKNESS
             };
             enum Size
             {
                 BIG,
                 MEDIUM,
                 SMALL
             };

      static bool m_identified[9];

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Potion(Type = HEALING, Size = BIG, int am = 1, sf::Vector2i pos = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Potion(Potion const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the item.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Potion(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the potion's type.
             ///
             /// The possible values are:
             /// - HEALING
             /// - MAGIC
             /// - STRENGTH
             /// - DEXTERITY
             /// - SPEED
             /// - REGENERATION
             /// - POISON
             /// - SLOWNESS
             /// - WEAKNESS
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return m_type; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the potion's size.
             ///
             /// The possible values are:
             /// - BIG
             /// - MEDIUM
             /// - SMALL
             ////////////////////////////////////////////////////////////////////////
             Size getSize() const { return m_size; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reveals the potion's properties.
             ////////////////////////////////////////////////////////////////////////
     virtual void reveal() override { m_identified[m_type] = true; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the potion is discovered.
             ////////////////////////////////////////////////////////////////////////
     virtual bool isDiscovered() const override { return m_identified[m_type]; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the potion's name.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the potion's description.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the potion's position relatively to the grid marked out
             /// by the level's tile map.
             ////////////////////////////////////////////////////////////////////////
             void setPosition(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the potion's position relatively to the graphics card's
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
             void setGridPosition(sf::Vector2i) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the book from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the book to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type m_type;
             Size m_size;
    };

}
