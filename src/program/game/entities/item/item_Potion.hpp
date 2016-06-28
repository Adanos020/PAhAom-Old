/**
 * @file src/program/game/item/item_Potion.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_Potion_hpp
#define item_Potion_hpp

#include "item.hpp"

namespace rr {

    class Potion : public Discoverable {
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
        } effect_;
        enum Size {
            SMALL,
            MEDIUM,
            BIG
        } size_;

         Potion(Effect, Size, int am = 1, sf::Vector2i pos = sf::Vector2i(0, 0));
         Potion(Potion const&);
        ~Potion() {}

        virtual Entity* clone () const override { return new Potion(*this); }
        virtual Entity* create() const override { return new Potion(HEALING, SMALL); }

        virtual void draw           (sf::RenderWindow&) override;
        virtual void reveal         ()                  override;

        void         setPosition    (sf::Vector2i)      override;
        void         setRealPosition(sf::Vector2f pos)  override;
    };

}

#endif // item_Potion_hpp
