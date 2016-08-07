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
    private: virtual void           initialize()                  override;
    
    public:  enum Type {
                 GOLDEN,
                 SILVER,
                 BRONZE
             } type_;
             enum Size {
                 SMALL,
                 BIG
             } size_;
         
             Coin(Type = GOLDEN, Size = SMALL, int am = 1, sf::Vector2u pos = sf::Vector2u(0, 0));
             Coin(Coin const&);
         
             virtual Entity*        clone          ()                               const override { return new Coin(*this); }
         
             virtual sf::String     getName        ()                               const override;
             virtual sf::String     getDescription ()                               const override;
         
             virtual std::ifstream& operator<<(std::ifstream&)                            override;
             virtual std::ofstream& operator>>(std::ofstream&)                            override;
	};

}

#endif // ITEM_COIN_HPP
