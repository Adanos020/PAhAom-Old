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
    private: virtual void           initialize    ()                  override;
    
    public:  Food();
             Food(Food const&);
            ~Food();
         
             virtual Entity*        clone         () const            override { return new Food(*this); }
             virtual Entity*        create        () const            override { return new Food(); }
             
         
             virtual void           draw          (sf::RenderWindow&) override;
         
             virtual sf::String     getName       () const            override;
             virtual sf::String     getDescription() const            override;
         
             virtual std::ifstream& operator<<(std::ifstream&) override;
             virtual std::ofstream& operator>>(std::ofstream&) override;
    };

}

#endif // item_Food_hpp
