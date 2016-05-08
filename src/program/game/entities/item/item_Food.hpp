/**
 * @file src/program/game/item/item_Food.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_Food_hpp
#define item_Food_hpp

#include "item.hpp"

namespace rr {

    class Food : public Item {
    private:
    public:
         Food();
        ~Food();

        virtual void draw (sf::RenderWindow&) override;
    };

}

#endif // item_Food_hpp
