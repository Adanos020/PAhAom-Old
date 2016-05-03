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

	class Cash : public Item {
    public:
        enum Type {
            BRONZE,
            SILVER,
            GOLDEN
        } type;
         Cash(Type, int am, sf::Vector2i pos);
        ~Cash();

        virtual void draw      (sf::RenderWindow&) override;
        virtual void update    ()                  override;
    private:
	};

}

#endif // item_Cash_hpp

