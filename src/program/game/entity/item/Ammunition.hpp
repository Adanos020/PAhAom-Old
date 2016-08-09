/**
 * @file src/program/game/item/Ammunition.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_AMMUNITION_HPP
#define ITEM_AMMUNITION_HPP

#include "Item.hpp"

namespace rr {

    class Ammunition : public Item {
    private: virtual void           initialize    ()           override;

    public:  enum Type {
                 ARROW,
                 BOLT,
                 STONE,
                 SHURIKEN
             }

             Ammunition(Type = ARROW, int amount = 1, sf::Vector2u position = sf::Vector2u(0, 0));
             Ammunition(Ammunition const&);

             Type                   getType       () const              { return type_; }

             virtual Entity*        clone         () const     override { return new Ammunition(*this); }
         
             virtual sf::String     getName       () const     override;
             virtual sf::String     getDescription() const     override;

             virtual std::ifstream& operator<<(std::ifstream&) override;
             virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type type_;
    };

}

#endif // ITEM_AMMUNITION_HPP
