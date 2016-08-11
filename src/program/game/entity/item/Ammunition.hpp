/**
 * @file src/program/game/item/Ammunition.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_AMMUNITION_HPP
#define ITEM_AMMUNITION_HPP

#include "Item.hpp"

namespace rr {

    class Ammunition : public Item {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the ammunition.
             ////////////////////////////////////////////////////////////////////////
     virtual void           initialize    ()           override;

    public:  enum Type {
                 ARROW,
                 BOLT,
                 ROCKS,
                 SHURIKEN
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Ammunition(Type = ARROW, int amount = 1, sf::Vector2i position = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Ammunition(Ammunition const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the ammunition.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Ammunition(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the ammunition's type.
             ///
             /// The possible values are:
             /// - ARROW (required by a bow)
             /// - BOLT (required by a crossbow)
             /// - ROCKS (required by a splingshot)
             /// - SHURIKEN (thrown ammunition)
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return type_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the ammunition's name.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the ammunition's description.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the ammunition from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the ammunition to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type type_;
    };

}

#endif // ITEM_AMMUNITION_HPP
