/**
 * @file src/program/game/item/item_Book.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_Book_hpp
#define item_Book_hpp

#include "item.hpp"

namespace rr {

    class Book :public Discoverable, public Item {
    private:
    public:
         Book();
        ~Book();

        virtual void draw      (sf::RenderWindow&) override;
        virtual void update    ()                  override;
    };

}

#endif // item_Book_hpp
