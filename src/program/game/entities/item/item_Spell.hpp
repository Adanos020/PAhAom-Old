/**
 * @file src/program/game/item/item_Spell.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_Spell_hpp
#define item_Spell_hpp

#include "item.hpp"

namespace rr {

    class Spell : public Item, public Discoverable {
    public:
        enum Type {
            HEAL,
            FIREBOLT,
            LIGHTNING,
            ICE_BULLET,
            TELEPORT,
            FIRE_RAIN,
            STORM,
            ICE_WAVE,
            TIME_FREEZING,
            IDENTIFY,
            UNCURSE
        } type_;

         Spell(Type, int am, sf::Vector2i pos = sf::Vector2i(0, 0));
        ~Spell() {}

        virtual void draw           (sf::RenderWindow&) override;
        virtual void reveal         ()                  override;

        void         setPosition    (sf::Vector2i)      override;
        void         setRealPosition(sf::Vector2f pos)  override;
    };

}

#endif // item_Spell_hpp
