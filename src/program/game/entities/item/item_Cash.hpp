/**
 * @file src/program/game/item/item_Cash.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_Cash_hpp
#define item_Cash_hpp

#include "item.hpp"

namespace rr {

//class Item;

	class Cash :public Item {
    public:
        enum Type {
            BRONZE,
            SILVER,
            GOLDEN
        };
         Cash(Type, int am, sf::Vector2f pos);
        ~Cash();

        virtual void draw      (sf::RenderWindow&) override;
        virtual void update    ()                  override;
    private:
        Type type;
	};

}

#endif // item_Cash_hpp

