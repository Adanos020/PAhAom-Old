/**
 * @file src/program/game/item/item_Spell.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_Spell_hpp
#define item_Spell_hpp

#include "item.hpp"

namespace rr {

    class Spell : public Item {
    private:
    public:
         Spell();
        ~Spell();

        virtual void draw (sf::RenderWindow&) override;
    };

}

#endif // item_Spell_hpp
