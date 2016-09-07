/**
 * @file src/program/game/item/Coin.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef ITEM_COIN_HPP
#define ITEM_COIN_HPP

#include "Item.hpp"

namespace rr
{

    class Coin : public Item
    {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the coin.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type
             {
                 GOLDEN,
                 SILVER,
                 BRONZE
             };
             enum Size
             {
                 SMALL,
                 BIG
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Coin(Type = GOLDEN, Size = SMALL, int am = 1, sf::Vector2i pos = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Coin(Coin const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the coin.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Coin(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the coin's type.
             ///
             /// The possible values are:
             /// - GOLDEN
             /// - SLIVER
             /// - BRONZE
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return m_type; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the coin's size.
             ///
             /// The possible values are:
             /// - SMALL
             /// - BIG
             ////////////////////////////////////////////////////////////////////////
             Size getSize() const { return m_size; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the coin's name.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the coin's description.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the coin from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the coin to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type m_type;
             Size m_size;
    };

}

#endif // ITEM_COIN_HPP
