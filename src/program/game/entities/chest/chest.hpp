/**
 * @file src/program/game/entities/chest/chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef chest_hpp
#define chest_hpp

#include <SFML/Graphics.hpp>

#include "../entities.hpp"

namespace rr {

    class Item;

    class Chest : public Entity {
    private:
        sf::Sprite body;
        Item*      item;
    public:
        enum Type {
            REGULAR,
            SPECIAL
        } type;
         Chest(Type t, Item*);
        ~Chest();

        void  setPosition(sf::Vector2f)      override;
        void  draw       (sf::RenderWindow&) override;

        Item* getItem    () { return item; }
    };

}

#endif // chest_hpp
