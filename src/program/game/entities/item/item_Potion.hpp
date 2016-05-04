/**
 * @file src/program/game/item/item_Potion.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_Potion_hpp
#define item_Potion_hpp

#include "item.hpp"

namespace rr {

    class Potion : public Discoverable, public Item {
    private:
    public:
        enum Effect {
            HEALING,
            MAGIC,
            STRENGTH,
            DEXTERITY,
            SPEED,
            REGENERATION,
            POISON,
            SLOWNESS,
            WEAKNESS
        } _effect;
        enum Size {
            SMALL,
            MEDIUM,
            BIG
        } _size;

         Potion(Effect, Size, int am, sf::Vector2i pos = sf::Vector2i(0, 0));
        ~Potion();

        virtual void draw       (sf::RenderWindow&) override;
        virtual void update     ()                  override;
        virtual void reveal     ()                  override;

        void         setPosition(sf::Vector2i)      override;
    };

}

#endif // item_Potion_hpp
