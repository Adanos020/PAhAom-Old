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
    
    public:  enum Type {
                 MEAT,
                 SANDVICH,
                 APPLE,
                 BEER,
                 HOT_DOG,
                 HAMBURGER,
                 BAGUETTE,
                 DUMPLING
             } type_;
    
             Food(Type = MEAT, int amount = 1, sf::Vector2i position = sf::Vector2i(0, 0));
             Food(Food const&);
         
             virtual Entity*        clone         () const            override { return new Food(*this); }
         
             virtual sf::String     getName       () const            override;
             virtual sf::String     getDescription() const            override;
         
             virtual std::ifstream& operator<<(std::ifstream&) override;
             virtual std::ofstream& operator>>(std::ofstream&) override;
    };

}

#endif // ITEM_FOOD_HPP
