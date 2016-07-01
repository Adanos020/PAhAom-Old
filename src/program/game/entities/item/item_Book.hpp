/**
 * @file src/program/game/item/item_Book.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_Book_hpp
#define item_Book_hpp

#include "item.hpp"

namespace rr {

    class Book : public Item {
    public:
        enum Type {
            CRAFTING,
            ALCHEMY,
            COLD_WEAPON_MASTERY,
            RANGED_WEAPON_MASTERY,
            EAGLE_EYE,
            MANA_REGEN,
            HEALTH_REGEN,
            FASTER_LEARNING,
            SPELLS_BOOK
        } type_;

         Book(Type, int am = 1, sf::Vector2i pos = sf::Vector2i(0, 0));
         Book(Book const&);
        ~Book() {}

        virtual Entity* clone          ()            const override { return new Book(*this); }
        virtual Entity* create         ()            const override { return new Book(CRAFTING); }
        
        virtual void    draw           (sf::RenderWindow&) override;

        void            setPosition    (sf::Vector2i)      override;
        void            setRealPosition(sf::Vector2f pos)  override;
    };

}

#endif // item_Book_hpp
