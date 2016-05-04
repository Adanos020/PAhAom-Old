/**
 * @file src/program/game/item/item_Coin.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_Coin_hpp
#define item_Coin_hpp

#include "item.hpp"

namespace rr {

//class Item;

	class Coin : public Item {
    public:
        enum Type {
            BRONZE,
            SILVER,
            GOLDEN
        } _type;
        enum Size {
            SMALL,
            BIG
        } _size;

         Coin(Type, Size, int am, sf::Vector2i pos);
        ~Coin();

        virtual void draw      (sf::RenderWindow&) override;
        virtual void update    ()                  override;
    private:
	};

}

#endif // item_Coin_hpp

