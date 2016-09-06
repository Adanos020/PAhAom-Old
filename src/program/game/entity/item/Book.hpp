/**
 * @file src/program/game/item/item_Book.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_BOOK_HPP
#define ITEM_BOOK_HPP

#include "Item.hpp"

namespace rr
{

    class Book : public Item
    {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the book.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type
             {
                 CRAFTING,
                 ALCHEMY,
                 MELEE_WEAPON_MASTERY,
                 RANGED_WEAPON_MASTERY,
                 EAGLE_EYE,
                 MANA_REGEN,
                 HEALTH_REGEN,
                 FASTER_LEARNING,
                 SPELLS_BOOK
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Book(Type = CRAFTING, int am = 1, sf::Vector2i pos = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Book(Book const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the book.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Book(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the book's type.
             ///
             /// The possible values are:
             /// - CRAFTING
             /// - ALCHEMY
             /// - MELEE_WEAPON_MASTERY
             /// - RANGED_WEAPON_MASTERY
             /// - EAGLE_EYE
             /// - MANA_REGEN
             /// - HEALTH_REGEN
             /// - FASTER_LEARNING
             /// - SPELLS_BOOK
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return type_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the book's position relatively to the grid marked out by
             /// the level's tile map.
             ////////////////////////////////////////////////////////////////////////
             void setGridPosition(sf::Vector2i) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the book's position relatively to the graphics card's
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
             void setPosition(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the book's name.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the book's description.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the book from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the book to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type type_;
    };

}

#endif // ITEM_BOOK_HPP
