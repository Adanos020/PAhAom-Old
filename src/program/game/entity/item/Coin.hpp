/**
 * @file src/program/game/item/Coin.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_COIN_HPP
#define ITEM_COIN_HPP

#include "Item.hpp"

namespace rr {

    class Coin : public Item {
    private: virtual void           initialize     ()          override;
    
    public:  enum Type {
                 GOLDEN,
                 SILVER,
                 BRONZE
             };
             enum Size {
                 SMALL,
                 BIG
             };

             Coin(Type = GOLDEN, Size = SMALL, int am = 1, sf::Vector2u pos = sf::Vector2u(0, 0));
             Coin(Coin const&);

             Type                   getType        () const             { return type_; }
             Size                   getSize        () const             { return size_; }

             virtual Entity*        clone          () const    override { return new Coin(*this); }

             virtual sf::String     getName        () const    override;
             virtual sf::String     getDescription () const    override;

             virtual std::ifstream& operator<<(std::ifstream&) override;
             virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type type_;
             Size size_;
    };

}

#endif // ITEM_COIN_HPP
