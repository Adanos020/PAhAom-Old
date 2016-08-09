/**
 * @file src/program/game/item/Potion.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_POTION_HPP
#define ITEM_POTION_HPP

#include "Item.hpp"

namespace rr {

    class Potion : public Discoverable {
    private: virtual void   initialize     ()               override;
    
    public:  enum Type {
                 HEALING,
                 MAGIC,
                 STRENGTH,
                 DEXTERITY,
                 SPEED,
                 REGENERATION,
                 POISON,
                 SLOWNESS,
                 WEAKNESS
             };
             enum Size {
                 BIG,
                 MEDIUM,
                 SMALL
             };

      static bool identified_[9];

             Potion(Type = HEALING, Size = BIG, int am = 1, sf::Vector2u pos = sf::Vector2u(0, 0));
             Potion(Potion const&);

             Type           getType        () const                  { return type_; }
             Size           getSize        () const                  { return size_; }

     virtual Entity*        clone          () const         override { return new Potion(*this); }

     virtual void           reveal         ()               override { identified_[type_] = true; }
     virtual bool           isDiscovered   () const         override { return identified_[type_]; }

     virtual sf::String     getName        () const         override;
     virtual sf::String     getDescription () const         override;

             void           setPosition    (sf::Vector2f)   override;
             void           setGridPosition(sf::Vector2u)   override;

     virtual std::ifstream& operator<<     (std::ifstream&) override;
     virtual std::ofstream& operator>>     (std::ofstream&) override;

    private: Type type_;
             Size size_;
    };

}

#endif // ITEM_POTION_HPP
