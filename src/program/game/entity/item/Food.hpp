/**
 * @file src/program/game/item/Food.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_FOOD_HPP
#define ITEM_FOOD_HPP

#include "Item.hpp"

namespace rr {

    class Food : public Item {
    private: virtual void           initialize    ()                  override;
    
    public:  Food();
             Food(Food const&);
         
             virtual Entity*        clone         () const            override { return new Food(*this); }
         
             virtual sf::String     getName       () const            override;
             virtual sf::String     getDescription() const            override;
         
             virtual std::ifstream& operator<<(std::ifstream&) override;
             virtual std::ofstream& operator>>(std::ofstream&) override;
    };

}

#endif // ITEM_FOOD_HPP
